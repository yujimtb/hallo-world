// SPDX-License-Identifier: GPL-2.0-only
#include <linux/module.h>
#include <linux/of.h>

#include "nh1_mic_overlay_blob.h"

static int overlay_id = -1;

static int __init nh1_mic_overlay_init(void)
{
	int ret;

	ret = of_overlay_fdt_apply(nh1_mic_overlay_dtbo,
				   nh1_mic_overlay_dtbo_len,
				   &overlay_id, NULL);
	if (ret) {
		pr_err("nh1_mic_overlay: apply failed: %d\n", ret);
		return ret;
	}

	pr_info("nh1_mic_overlay: applied overlay id %d\n", overlay_id);
	return 0;
}

static void __exit nh1_mic_overlay_exit(void)
{
	int ret;

	if (overlay_id < 0)
		return;

	ret = of_overlay_remove(&overlay_id);
	if (ret)
		pr_err("nh1_mic_overlay: remove failed: %d\n", ret);
	else
		pr_info("nh1_mic_overlay: removed\n");
}

module_init(nh1_mic_overlay_init);
module_exit(nh1_mic_overlay_exit);

MODULE_AUTHOR("yuji mitobe <mitobex7@gmail.com>");
MODULE_DESCRIPTION("Nothing Phone (1) live microphone DT overlay validator");
MODULE_LICENSE("GPL");
