#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbd97005b, "module_layout" },
	{ 0xf72f2e16, "cdev_del" },
	{ 0x5bbe49f4, "__init_waitqueue_head" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x4a91e5dd, "cdev_add" },
	{ 0xc72c11da, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x5f754e5a, "memset" },
	{ 0x3dcf1ffa, "__wake_up" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x86332725, "__stack_chk_fail" },
	{ 0x2cfde9a2, "warn_slowpath_fmt" },
	{ 0x49970de8, "finish_wait" },
	{ 0x647af474, "prepare_to_wait_event" },
	{ 0x1000e51, "schedule" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "8FF06C12A735CB01A768F24");
