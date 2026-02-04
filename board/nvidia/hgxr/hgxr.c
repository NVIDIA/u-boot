#include <asm/io.h>
#include <common.h>
#include <dm.h>
#include <environment.h>
#include <i2c.h>

#define CPLD_I2C_BUS           5
#define CPLD_I2C_ADDR          0xb
#define CPLD_USER_STRAP_OFFSET 0x9
#define CPLD_USER_STRAP_SHIFT  0
#define CPLD_USER_STRAP_MASK   0x1f

#define INVALID_USERSTRAP 0xff

/**
 * read_userstrap() - reads the USER_STRAP register from the CPLD register table
 *
 * @return valid strap if success, INVALID_USERSTRAP if error
 */
uint8_t read_userstrap(void)
{
    int ret;
    uint8_t strap;
    struct udevice *cpld = NULL;

    ret = i2c_get_chip_for_busnum(CPLD_I2C_BUS, CPLD_I2C_ADDR, 1, &cpld);
    if (ret)
    {
        printf("Failed to get I2C %d bus\n", CPLD_I2C_BUS);
        return INVALID_USERSTRAP;
    }

    ret = dm_i2c_read(cpld, CPLD_USER_STRAP_OFFSET, &strap, sizeof(strap));
    if (ret)
    {
        printf("Failed reading regtbl\n");
        return INVALID_USERSTRAP;
    }

    return CPLD_USER_STRAP_MASK & (strap >> CPLD_USER_STRAP_SHIFT);
}

bool is_factory_reset(void)
{
    char *openbmconce =  env_get("openbmconce");
    return openbmconce && strncmp(openbmconce, "factory-reset", 24) == 0;
}

int board_early_init_f(void)
{
    return 0;
}

int board_late_init(void)
{
    bool factory_reset;
    uint8_t cur_userstrap;
    uint8_t userstrap;
    int ret;
    bool save_env = false;
    char *force_default_vars[] = {"bootcmd"};

    // Always default bootcmd unless preboot is present (escape hatch)
    if (!env_get("preboot"))
    {
        ret = set_default_vars(1, force_default_vars, H_FORCE);
        if (ret)
        {
            printf("Failed to reset env vars!\n");
        }
        else
        {
            save_env = true;
        }
    }

    factory_reset = is_factory_reset();
    cur_userstrap = env_get_ulong("userstrap", 10, INVALID_USERSTRAP);

    if (factory_reset || cur_userstrap == INVALID_USERSTRAP)
    {
        userstrap = read_userstrap();
        printf(
            "Read USER_STRAP from the CPLD factory_reset=%d, cur_userstrap=%#x, userstrap=%x\n",
            factory_reset,
            cur_userstrap,
            userstrap);

        ret = env_set_ulong("userstrap", userstrap);
        if (ret)
        {
            printf("Failed setting userstrap\n");
        }
        else
        {
            save_env = true;
        }
    }

    if (save_env)
    {
        ret = env_save();
        if (ret)
        {
            printf("Failed saving env\n");
        }
    }

    return 0;
}
