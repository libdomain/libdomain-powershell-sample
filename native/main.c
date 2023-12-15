#include <libdomain/common.h>
#include <libdomain/domain.h>
#include <libdomain/directory.h>
#include <libdomain/entry.h>
#include <libdomain/connection_state_machine.h>
#include <stdio.h>
#include <stdbool.h>
#include <talloc.h>

static char* LDAP_DIRECTORY_ATTRS[] = { "*", "+", NULL };

static void exit_callback(verto_ctx *ctx, verto_ev *ev)
{
    (void) ctx;
    (void) ev;

    verto_break(ctx);
}

static enum OperationReturnCode connection_on_error(int rc, void* unused_a, void* connection)
{
    (void)(unused_a);

    verto_break(((ldap_connection_ctx_t*)connection)->base);

    fprintf(stderr, "Unable to perform operation!\n");

    exit(EXIT_FAILURE);

    return RETURN_CODE_SUCCESS;
}

static void connection_on_update(verto_ctx *ctx, verto_ev *ev)
{
    (void)(ctx);

    struct ldap_connection_ctx_t* connection = verto_get_private(ev);

    if (connection->state_machine->state == LDAP_CONNECTION_STATE_RUN)
    {
        verto_del(ev);

        search(connection, "", LDAP_SCOPE_BASE,
               "(objectClass=*)", LDAP_DIRECTORY_ATTRS, 0, NULL);
    }

    if (connection->state_machine->state == LDAP_CONNECTION_STATE_ERROR)
    {
        verto_break(ctx);

        fprintf(stderr, "Error encountered during bind!\n");
    }
}

int get_root_dse()
{
    TALLOC_CTX* talloc_ctx = talloc_new(NULL);

    char *ldap_server   = "ldap://127.0.0.1:3890";
    char *ldap_username = "admin";
    char *ldap_password = "password";
    char *ldap_bind_dn  = "dc=domain,dc=alt";

    const int update_interval = 1000;

    ld_config_t *config = NULL;
    config = ld_create_config(talloc_ctx, ldap_server, 0, LDAP_VERSION3, ldap_bind_dn,
                              ldap_username, ldap_password, true, false, false, true,
                              update_interval, "", "", "");

    const int exit_time = 10000;

    LDHandle *handle = NULL;
    ld_init(&handle, config);

    ld_install_default_handlers(handle);
    ld_install_handler(handle, connection_on_update, update_interval);
    ld_install_handler(handle, exit_callback, exit_time);
    ld_install_error_handler(handle, connection_on_error);

    ld_exec(handle);

    ld_free(handle);

    talloc_free(talloc_ctx);

    return 0;
}
