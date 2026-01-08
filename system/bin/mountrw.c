#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define CMD_BUF 512
#define LINE_BUF 1024
#define STATE_LEN 16

/* ======================
 * Funciones básicas
 * ====================== */

/**
 * Ejecuta un comando en el sistema y devuelve su código de retorno.
 */
static int execute_command(const char *cmd) {
    int rc = system(cmd);
    if (rc == -1) {
        fprintf(stderr, "Error ejecutando comando '%s': %s\n", cmd, strerror(errno));
    }
    return rc;
}

/**
 * Obtiene el estado real del montaje (RW/RO/UNKNOWN)
 */
static void get_mount_state(const char *mount_point, char *state, size_t state_size) {
    char cmd[CMD_BUF];
    snprintf(cmd, sizeof(cmd), "mount | grep ' on %s ' | sed 's/.*(\\(.*\\)).*/\\1/'", mount_point);

    FILE *fp = popen(cmd, "r");
    if (!fp) {
        snprintf(state, state_size, "UNKNOWN");
        return;
    }

    char opts[LINE_BUF];
    if (fgets(opts, sizeof(opts), fp)) {
        char *opt = strtok(opts, ",\n");
        while (opt) {
            if (strcmp(opt, "rw") == 0) {
                snprintf(state, state_size, "RW");
                break;
            } else if (strcmp(opt, "ro") == 0) {
                snprintf(state, state_size, "RO");
                break;
            }
            opt = strtok(NULL, ",\n");
        }
    }
    pclose(fp);
}

/**
 * Fuerza un montaje en modo RW.
 */
static void force_rw(const char *mount_point) {
    char cmd[CMD_BUF];
    int rc;

    snprintf(cmd, sizeof(cmd), "mount -o remount,rw %s 2>&1", mount_point);
    rc = execute_command(cmd);

    if (rc != 0) {
        snprintf(cmd, sizeof(cmd), "mount --bind %s %s 2>&1", mount_point, mount_point);
        rc = execute_command(cmd);
        if (rc != 0) {
            printf("%s: FORCE FAILED\n", mount_point);
            return;
        }
    }

    char state[STATE_LEN] = "UNKNOWN";
    get_mount_state(mount_point, state, sizeof(state));
    printf("%s: FORCED %s\n", mount_point, state);
}

/**
 * Lista todos los puntos de montaje y su estado.
 */
static void list_mounts() {
    FILE *mounts = popen("mount", "r");
    if (!mounts) {
        perror("popen mount");
        return;
    }

    char line[LINE_BUF];
    while (fgets(line, sizeof(line), mounts)) {
        char *mp = NULL;
        char *tok = strtok(line, " ");
        while (tok) {
            if (strcmp(tok, "on") == 0) {
                mp = strtok(NULL, " ");
                break;
            }
            tok = strtok(NULL, " ");
        }
        if (mp && strlen(mp) > 0) {
            char state[STATE_LEN] = "UNKNOWN";
            get_mount_state(mp, state, sizeof(state));
            printf("%s: %s\n", mp, state);
        }
    }

    pclose(mounts);
}

/**
 * Muestra la ayuda del programa.
 */
static void show_help() {
    printf(
        "Uso: mountctl [--comando] [opciones]\n\n"
        "Comandos:\n"
        "  --help               Muestra esta ayuda\n"
        "  --list               Lista todos los montajes con su estado\n"
        "  --force <mount>      Fuerza un montaje en modo RW\n"
        "  --status <mount>     Muestra el estado (RW/RO) de un montaje específico\n"
    );
}

/* ======================
 * Función principal
 * ====================== */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        show_help();
        return 0;
    }

    if (strcmp(argv[1], "--help") == 0) {
        show_help();
    } else if (strcmp(argv[1], "--list") == 0) {
        list_mounts();
    } else if (strcmp(argv[1], "--force") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: Debe especificar un punto de montaje\n");
            return 1;
        }
        force_rw(argv[2]);
    } else if (strcmp(argv[1], "--status") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: Debe especificar un punto de montaje\n");
            return 1;
        }
        char state[STATE_LEN] = "UNKNOWN";
        get_mount_state(argv[2], state, sizeof(state));
        printf("%s: %s\n", argv[2], state);
    } else {
        fprintf(stderr, "Comando desconocido: %s\n", argv[1]);
        show_help();
        return 1;
    }

    return 0;
}
