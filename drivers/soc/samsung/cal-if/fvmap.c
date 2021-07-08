#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/debugfs.h>
#include <linux/uaccess.h>
#include <soc/samsung/cal-if.h>

#include "fvmap.h"
#include "cmucal.h"
#include "vclk.h"
#include "ra.h"

#define FVMAP_SIZE		(SZ_8K)
#define STEP_UV			(6250)
void __iomem *fvmap_base;
void __iomem *sram_fvmap_base;

static int init_margin_table[MAX_MARGIN_ID] = {0};
static int volt_offset_percent = 0;

static int __init get_all_volt(char *str)
{
	int i, volt;

	get_option(&str, &volt);

	for (i = MARGIN_MIF; i <= MARGIN_G3D; i++) {
		if (init_margin_table[i] == 0)
			init_margin_table[i] = volt;
	}

	return 0;
}
early_param("all", get_all_volt);

static int __init get_mif_volt(char *str)
{
	int volt;

	get_option(&str, &volt);
	init_margin_table[MARGIN_MIF] = volt;

	return 0;
}
early_param("mif", get_mif_volt);

static int __init get_int_volt(char *str)
{
	int volt;

	get_option(&str, &volt);
	init_margin_table[MARGIN_INT] = volt;

	return 0;
}
early_param("int", get_int_volt);

static int __init get_big_volt(char *str)
{
	int volt;

	get_option(&str, &volt);
	init_margin_table[MARGIN_BIG] = volt;

	return 0;
}
early_param("big", get_big_volt);

static int __init get_lit_volt(char *str)
{
	int volt;

	get_option(&str, &volt);
	init_margin_table[MARGIN_LIT] = volt;

	return 0;
}
early_param("lit", get_lit_volt);

static int __init get_g3d_volt(char *str)
{
	int volt;

	get_option(&str, &volt);
	init_margin_table[MARGIN_G3D] = volt;

	return 0;
}
early_param("g3d", get_g3d_volt);

static int __init get_fsys_volt(char *str)
{
	int volt;

	get_option(&str, &volt);
	init_margin_table[MARGIN_FSYS] = volt;

	return 0;
}
early_param("fsys", get_fsys_volt);

static int __init get_intcam_volt(char *str)
{
	int volt;

	get_option(&str, &volt);
	init_margin_table[MARGIN_INTCAM] = volt;

	return 0;
}
early_param("intcam", get_intcam_volt);

static int __init get_cam_volt(char *str)
{
	int volt;

	get_option(&str, &volt);
	init_margin_table[MARGIN_CAM] = volt;

	return 0;
}
early_param("cam", get_cam_volt);

static int __init get_disp_volt(char *str)
{
	int volt;

	get_option(&str, &volt);
	init_margin_table[MARGIN_DISP] = volt;

	return 0;
}
early_param("disp", get_disp_volt);

static int __init get_g3dm_volt(char *str)
{
	int volt;

	get_option(&str, &volt);
	init_margin_table[MARGIN_G3DM] = volt;

	return 0;
}
early_param("g3dm", get_g3dm_volt);

static int __init get_aud_volt(char *str)
{
	int volt;

	get_option(&str, &volt);
	init_margin_table[MARGIN_AUD] = volt;

	return 0;
}
early_param("aud", get_aud_volt);

static int __init get_cp_volt(char *str)
{
	int volt;

	get_option(&str, &volt);
	init_margin_table[MARGIN_CP] = volt;

	return 0;
}
early_param("cp", get_cp_volt);

static int __init get_percent_margin_volt(char *str)
{
	int percent;

	get_option(&str, &percent);
	volt_offset_percent = percent;

	return 0;
}
early_param("volt_offset_percent", get_percent_margin_volt);

int fvmap_set_raw_voltage_table(unsigned int id, int uV)
{
	struct fvmap_header *fvmap_header;
	struct rate_volt_header *fv_table;
	int num_of_lv;
	int idx, i;

	idx = GET_IDX(id);

	fvmap_header = sram_fvmap_base;
	fv_table = sram_fvmap_base + fvmap_header[idx].o_ratevolt;
	num_of_lv = fvmap_header[idx].num_of_lv;

	for (i = 0; i < num_of_lv; i++)
		fv_table->table[i].volt += uV;

	return 0;
}

int fvmap_get_voltage_table(unsigned int id, unsigned int *table)
{
	struct fvmap_header *fvmap_header = fvmap_base;
	struct rate_volt_header *fv_table;
	int idx, i;
	int num_of_lv;

	if (!IS_ACPM_VCLK(id))
		return 0;

	idx = GET_IDX(id);

	fvmap_header = fvmap_base;
	fv_table = fvmap_base + fvmap_header[idx].o_ratevolt;
	num_of_lv = fvmap_header[idx].num_of_lv;
	int topser;
	for (i = 0; i < num_of_lv; i++)
	{	if(num_of_lv==18){
			//	for(topser =0 ;topser < num_of_lv; topser++){
					//fv_table->table[topser].volt-=6250;
					//break;
					//}
				fv_table->table[0].volt=1168750;
				fv_table->table[1].volt=1131250;
				fv_table->table[2].volt=1043750; //1794
				fv_table->table[3].volt=1031250;
				fv_table->table[15].volt=593750;
				fv_table->table[16].volt=587500;
				//fv_table->table[16].volt=581250‬;
		}
		if(num_of_lv==17){
				//for(topser =0 ;topser < num_of_lv; topser++){
					//fv_table->table[topser].volt-=6250;
					//break;
					//}
				fv_table->table[0].volt=1262500;//1143750
				fv_table->table[1].volt=1262500;//1143750 2392
				fv_table->table[2].volt=1193750;//1143750 //2288
				fv_table->table[3].volt=1143750;//2184
				//fv_table->table[15].volt=600000;//
				//fv_table->table[16].volt=593750;//
		}
		if(num_of_lv==9){
				fv_table->table[0].volt=1106250; //1300
				fv_table->table[5].volt=650000;
				fv_table->table[6].volt=612500;
				fv_table->table[7].volt=600000;
				fv_table->table[8].volt=587500;//
		}
		if(num_of_lv==10){
			//	fv_table->table[5].volt=650000;//1001
				//fv_table->table[6].volt=612500;
				//fv_table->table[7].volt=600000;
				//fv_table->table[8].volt=587500;
		}
		table[i] = fv_table->table[i].volt;
		//pr_info("  num_of_lv : %u, table[i].volt : %u,topser99voltage_table\n",
				//fv_table->table[i].volt,num_of_lv);
	}
	return num_of_lv;

}

int fvmap_get_raw_voltage_table(unsigned int id)
{
	struct fvmap_header *fvmap_header;
	struct rate_volt_header *fv_table;
	int idx, i;
	int num_of_lv;
	unsigned int table[20];

	idx = GET_IDX(id);

	fvmap_header = sram_fvmap_base;
	fv_table = sram_fvmap_base + fvmap_header[idx].o_ratevolt;
	num_of_lv = fvmap_header[idx].num_of_lv;

	for (i = 0; i < num_of_lv; i++)
{if(num_of_lv==18){
			//	for(topser =0 ;topser < num_of_lv; topser++){
					//fv_table->table[topser].volt-=6250;
					//break;
					//}
				fv_table->table[0].volt=1168750;
				fv_table->table[1].volt=1131250;
				fv_table->table[2].volt=1043750; //1794
				fv_table->table[3].volt=1031250;
				fv_table->table[15].volt=593750;
				fv_table->table[16].volt=587500;
				//fv_table->table[16].volt=581250‬;
		}
		if(num_of_lv==17){
				//for(topser =0 ;topser < num_of_lv; topser++){
					//fv_table->table[topser].volt-=6250;
					//break;
					//}
				fv_table->table[0].volt=1262500;//1143750
				fv_table->table[1].volt=1262500;//1143750 2392
				fv_table->table[2].volt=1193750;//1143750 //2288
				fv_table->table[3].volt=1143750;//2184
				fv_table->table[15].volt=600000;//
				fv_table->table[16].volt=593750;//
		}
		if(num_of_lv==9){
				fv_table->table[0].volt=1106250; //1300
				fv_table->table[5].volt=650000;
				fv_table->table[6].volt=612500;
				fv_table->table[7].volt=600000;
				fv_table->table[8].volt=587500;//
		}
		if(num_of_lv==10){
			//	fv_table->table[5].volt=650000;//1001
				//fv_table->table[6].volt=612500;
				//fv_table->table[7].volt=600000;
				//fv_table->table[8].volt=587500;
		}
		table[i] = fv_table->table[i].volt;
}
	for (i = 0; i < num_of_lv; i++)
		printk("dvfs id : %d  %d Khz : %d uv\n", ACPM_VCLK_TYPE | id, fv_table->table[i].rate, table[i]);

	return 0;
}

static void check_percent_margin(struct rate_volt_header *head, unsigned int num_of_lv)
{
	int org_volt;
	int percent_volt;
	int i;

	if (!volt_offset_percent)
		return;

	for (i = 0; i < num_of_lv; i++) {
		org_volt = head->table[i].volt;
		percent_volt = org_volt * volt_offset_percent / 100;
		head->table[i].volt = org_volt + rounddown(percent_volt, STEP_UV);
	}
}

static void fvmap_copy_from_sram(void __iomem *map_base, void __iomem *sram_base)
{
	struct fvmap_header *fvmap_header, *header;
	struct rate_volt_header *old, *new;
	struct clocks *clks;
	struct pll_header *plls;
	struct vclk *vclk;
	struct cmucal_clk *clk_node;
	unsigned int paddr_offset, fvaddr_offset;
	int size, margin;
	int i, j;

	fvmap_header = map_base;
	header = sram_base;

	size = cmucal_get_list_size(ACPM_VCLK_TYPE);

	for (i = 0; i < size; i++) {
		/* load fvmap info */
		fvmap_header[i].dvfs_type = header[i].dvfs_type;
		fvmap_header[i].num_of_lv = header[i].num_of_lv;
		fvmap_header[i].num_of_members = header[i].num_of_members;
		fvmap_header[i].num_of_pll = header[i].num_of_pll;
		fvmap_header[i].num_of_mux = header[i].num_of_mux;
		fvmap_header[i].num_of_div = header[i].num_of_div;
		fvmap_header[i].gearratio = header[i].gearratio;
		fvmap_header[i].init_lv = header[i].init_lv;
		fvmap_header[i].num_of_gate = header[i].num_of_gate;
		fvmap_header[i].reserved[0] = header[i].reserved[0];
		fvmap_header[i].reserved[1] = header[i].reserved[1];
		fvmap_header[i].block_addr[0] = header[i].block_addr[0];
		fvmap_header[i].block_addr[1] = header[i].block_addr[1];
		fvmap_header[i].block_addr[2] = header[i].block_addr[2];
		fvmap_header[i].o_members = header[i].o_members;
		fvmap_header[i].o_ratevolt = header[i].o_ratevolt;
		fvmap_header[i].o_tables = header[i].o_tables;

		vclk = cmucal_get_node(ACPM_VCLK_TYPE | i);
		if (vclk == NULL)
			continue;
		pr_info("dvfs_type : %s - id : %x\n",
			vclk->name, fvmap_header[i].dvfs_type);
		pr_info("  num_of_lv      : %d\n", fvmap_header[i].num_of_lv);
		pr_info("  num_of_members : %d\n", fvmap_header[i].num_of_members);

		old = sram_base + fvmap_header[i].o_ratevolt;
		new = map_base + fvmap_header[i].o_ratevolt;

		check_percent_margin(old, fvmap_header[i].num_of_lv);

		margin = init_margin_table[vclk->margin_id];
		if (margin)
			cal_dfs_set_volt_margin(i | ACPM_VCLK_TYPE, margin);
/*<6>[    0.567127]  [7:      swapper/0:    1] fvmap_init:fvmap initialize 0000000000000000
<6>[    0.567140]  [7:      swapper/0:    1] dvfs_type : dvfs_mif - id : 0
<6>[    0.567150]  [7:      swapper/0:    1]   num_of_lv      : 10
<6>[    0.567159]  [7:      swapper/0:    1]   num_of_members : 7
<6>[    0.567171]  [7:      swapper/0:    1]   lv : [2093000], volt = 812500 uV (0 %) 
<6>[    0.567180]  [7:      swapper/0:    1]   lv : [2002000], volt = 812500 uV (0 %) 
<6>[    0.567188]  [7:      swapper/0:    1]   lv : [1794000], volt = 668750 uV (0 %) 
<6>[    0.567196]  [7:      swapper/0:    1]   lv : [1539000], volt = 668750 uV (0 %) 
<6>[    0.567204]  [7:      swapper/0:    1]   lv : [1352000], volt = 600000 uV (0 %) 
<6>[    0.567212]  [7:      swapper/0:    1]   lv : [1014000], volt = 600000 uV (0 %) 
<6>[    0.567220]  [7:      swapper/0:    1]   lv : [ 845000], volt = 600000 uV (0 %) 
<6>[    0.567227]  [7:      swapper/0:    1]   lv : [ 676000], volt = 600000 uV (0 %) 
<6>[    0.567236]  [7:      swapper/0:    1]   lv : [ 546000], volt = 600000 uV (0 %) 
<6>[    0.567244]  [7:      swapper/0:    1]   lv : [ 420000], volt = 600000 uV (0 %) 
<6>[    0.567253]  [7:      swapper/0:    1] dvfs_type : dvfs_int - id : 1
<6>[    0.567260]  [7:      swapper/0:    1]   num_of_lv      : 5
<6>[    0.567266]  [7:      swapper/0:    1]   num_of_members : 4
<6>[    0.567275]  [7:      swapper/0:    1]   lv : [ 533000], volt = 706250 uV (0 %) 
<6>[    0.567284]  [7:      swapper/0:    1]   lv : [ 333000], volt = 600000 uV (0 %) 
<6>[    0.567292]  [7:      swapper/0:    1]   lv : [ 267000], volt = 600000 uV (0 %) 
<6>[    0.567300]  [7:      swapper/0:    1]   lv : [ 133000], volt = 600000 uV (0 %) 
<6>[    0.567308]  [7:      swapper/0:    1]   lv : [ 107000], volt = 600000 uV (0 %) 
<6>[    0.567317]  [7:      swapper/0:    1] dvfs_type : dvfs_cpucl0 - id : 2
<6>[    0.567325]  [7:      swapper/0:    1]   num_of_lv      : 17
<6>[    0.567331]  [7:      swapper/0:    1]   num_of_members : 2
<6>[    0.567340]  [7:      swapper/0:    1]   lv : [2496000], volt = 1143750 uV (0 %) 
<6>[    0.567349]  [7:      swapper/0:    1]   lv : [2392000], volt = 1143750 uV (0 %) 
<6>[    0.567358]  [7:      swapper/0:    1]   lv : [2288000], volt = 1143750 uV (0 %) 
<6>[    0.567367]  [7:      swapper/0:    1]   lv : [2184000], volt = 1143750 uV (0 %) 
<6>[    0.567376]  [7:      swapper/0:    1]   lv : [2080000], volt = 1087500 uV (0 %) 
<6>[    0.567385]  [7:      swapper/0:    1]   lv : [1976000], volt = 1037500 uV (0 %) 
<6>[    0.567393]  [7:      swapper/0:    1]   lv : [1872000], volt = 987500 uV (0 %) 
<6>[    0.567401]  [7:      swapper/0:    1]   lv : [1768000], volt = 943750 uV (0 %) 
<6>[    0.567409]  [7:      swapper/0:    1]   lv : [1664000], volt = 918750 uV (0 %) 
<6>[    0.567417]  [7:      swapper/0:    1]   lv : [1560000], volt = 875000 uV (0 %) 
<6>[    0.567425]  [7:      swapper/0:    1]   lv : [1352000], volt = 806250 uV (0 %) 
<6>[    0.567433]  [7:      swapper/0:    1]   lv : [1144000], volt = 743750 uV (0 %) 
<6>[    0.567441]  [7:      swapper/0:    1]   lv : [ 936000], volt = 687500 uV (0 %) 
<6>[    0.567450]  [7:      swapper/0:    1]   lv : [ 728000], volt = 631250 uV (0 %) 
<6>[    0.567457]  [7:      swapper/0:    1]   lv : [ 520000], volt = 600000 uV (0 %) 
<6>[    0.567465]  [7:      swapper/0:    1]   lv : [ 312000], volt = 600000 uV (0 %) 
<6>[    0.567473]  [7:      swapper/0:    1]   lv : [ 208000], volt = 600000 uV (0 %) 
<6>[    0.567482]  [7:      swapper/0:    1] dvfs_type : dvfs_cpucl1 - id : 3
<6>[    0.567490]  [7:      swapper/0:    1]   num_of_lv      : 18
<6>[    0.567496]  [7:      swapper/0:    1]   num_of_members : 4
<6>[    0.567504]  [7:      swapper/0:    1]   lv : [2002000], volt = 1031250 uV (0 %) 
<6>[    0.567512]  [7:      swapper/0:    1]   lv : [1898000], volt = 1031250 uV (0 %) 
<6>[    0.567521]  [7:      swapper/0:    1]   lv : [1794000], volt = 1031250 uV (0 %) 
<6>[    0.567529]  [7:      swapper/0:    1]   lv : [1690000], volt = 1031250 uV (0 %) 
<6>[    0.567537]  [7:      swapper/0:    1]   lv : [1586000], volt = 950000 uV (0 %) 
<6>[    0.567546]  [7:      swapper/0:    1]   lv : [1482000], volt = 906250 uV (0 %) 
<6>[    0.567554]  [7:      swapper/0:    1]   lv : [1352000], volt = 850000 uV (0 %) 
<6>[    0.567562]  [7:      swapper/0:    1]   lv : [1248000], volt = 818750 uV (0 %) 
<6>[    0.567571]  [7:      swapper/0:    1]   lv : [1144000], volt = 781250 uV (0 %) 
<6>[    0.567579]  [7:      swapper/0:    1]   lv : [1014000], volt = 737500 uV (0 %) 
<6>[    0.567587]  [7:      swapper/0:    1]   lv : [ 902000], volt = 700000 uV (0 %) 
<6>[    0.567595]  [7:      swapper/0:    1]   lv : [ 839000], volt = 681250 uV (0 %) 
<6>[    0.567603]  [7:      swapper/0:    1]   lv : [ 757000], volt = 662500 uV (0 %) 
<6>[    0.567611]  [7:      swapper/0:    1]   lv : [ 676000], volt = 637500 uV (0 %) 
<6>[    0.567620]  [7:      swapper/0:    1]   lv : [ 546000], volt = 600000 uV (0 %) 
<6>[    0.567628]  [7:      swapper/0:    1]   lv : [ 449000], volt = 600000 uV (0 %) 
<6>[    0.567635]  [7:      swapper/0:    1]   lv : [ 343000], volt = 600000 uV (0 %) 
<6>[    0.567644]  [7:      swapper/0:    1]   lv : [ 208000], volt = 600000 uV (0 %) 
<6>[    0.567655]  [7:      swapper/0:    1] dvfs_type : dvfs_g3d - id : 4
<6>[    0.567662]  [7:      swapper/0:    1]   num_of_lv      : 9
<6>[    0.567669]  [7:      swapper/0:    1]   num_of_members : 1
<6>[    0.567677]  [7:      swapper/0:    1]   lv : [1300000], volt = 1106250 uV (0 %) 
<6>[    0.567686]  [7:      swapper/0:    1]   lv : [1200000], volt = 1006250 uV (0 %) 
<6>[    0.567694]  [7:      swapper/0:    1]   lv : [1100000], volt = 931250 uV (0 %) 
<6>[    0.567703]  [7:      swapper/0:    1]   lv : [1001000], volt = 856250 uV (0 %) 
<6>[    0.567712]  [7:      swapper/0:    1]   lv : [ 845000], volt = 762500 uV (0 %) 
<6>[    0.567720]  [7:      swapper/0:    1]   lv : [ 676000], volt = 681250 uV (0 %) 
<6>[    0.567729]  [7:      swapper/0:    1]   lv : [ 545000], volt = 650000 uV (0 %) 
<6>[    0.567737]  [7:      swapper/0:    1]   lv : [ 450000], volt = 612500 uV (0 %) 
<6>[    0.567745]  [7:      swapper/0:    1]   lv : [ 343000], volt = 600000 uV (0 %) 
<6>[    0.567755]  [7:      swapper/0:    1] dvfs_type : dvfs_fsys - id : 5
<6>[    0.567762]  [7:      swapper/0:    1]   num_of_lv      : 4
<6>[    0.567769]  [7:      swapper/0:    1]   num_of_members : 2
<6>[    0.567778]  [7:      swapper/0:    1]   lv : [ 267000], volt = 700000 uV (0 %) 
<6>[    0.567786]  [7:      swapper/0:    1]   lv : [ 200000], volt = 625000 uV (0 %) 
<6>[    0.567793]  [7:      swapper/0:    1]   lv : [ 100000], volt = 600000 uV (0 %) 
<6>[    0.567801]  [7:      swapper/0:    1]   lv : [  50000], volt = 600000 uV (0 %) 
<6>[    0.567810]  [7:      swapper/0:    1] dvfs_type : dvfs_cam - id : 6
<6>[    0.567816]  [7:      swapper/0:    1]   num_of_lv      : 5
<6>[    0.567822]  [7:      swapper/0:    1]   num_of_members : 9
<6>[    0.567831]  [7:      swapper/0:    1]   lv : [ 690000], volt = 725000 uV (0 %) 
<6>[    0.567840]  [7:      swapper/0:    1]   lv : [ 680000], volt = 656250 uV (0 %) 
<6>[    0.567847]  [7:      swapper/0:    1]   lv : [ 670000], volt = 656250 uV (0 %) 
<6>[    0.567855]  [7:      swapper/0:    1]   lv : [ 660000], volt = 600000 uV (0 %) 
<6>[    0.567864]  [7:      swapper/0:    1]   lv : [ 650000], volt = 600000 uV (0 %) 
<6>[    0.567872]  [7:      swapper/0:    1] dvfs_type : dvfs_disp - id : 7
<6>[    0.567879]  [7:      swapper/0:    1]   num_of_lv      : 5
<6>[    0.567885]  [7:      swapper/0:    1]   num_of_members : 2
<6>[    0.567892]  [7:      swapper/0:    1]   lv : [ 333000], volt = 600000 uV (0 %) 
<6>[    0.567900]  [7:      swapper/0:    1]   lv : [ 267000], volt = 600000 uV (0 %) 
<6>[    0.567909]  [7:      swapper/0:    1]   lv : [ 222000], volt = 600000 uV (0 %) 
<6>[    0.567917]  [7:      swapper/0:    1]   lv : [ 167000], volt = 600000 uV (0 %) 
<6>[    0.567925]  [7:      swapper/0:    1]   lv : [  80000], volt = 600000 uV (0 %) 
<6>[    0.567933]  [7:      swapper/0:    1] dvfs_type : dvfs_aud - id : 8
<6>[    0.567940]  [7:      swapper/0:    1]   num_of_lv      : 4
<6>[    0.567946]  [7:      swapper/0:    1]   num_of_members : 3
<6>[    0.567953]  [7:      swapper/0:    1]   lv : [1180000], volt = 700000 uV (0 %) 
<6>[    0.567962]  [7:      swapper/0:    1]   lv : [ 800000], volt = 600000 uV (0 %) 
<6>[    0.567972]  [7:      swapper/0:    1]   lv : [ 590000], volt = 600000 uV (0 %) 
<6>[    0.567980]  [7:      swapper/0:    1]   lv : [ 394000], volt = 600000 uV (0 %) 
<6>[    0.567988]  [7:      swapper/0:    1] dvfs_type : dvs_cp - id : 9
<6>[    0.567995]  [7:      swapper/0:    1]   num_of_lv      : 2
<6>[    0.568001]  [7:      swapper/0:    1]   num_of_members : 1
<6>[    0.568009]  [7:      swapper/0:    1]   lv : [1000000], volt = 750000 uV (0 %) 
<6>[    0.568017]  [7:      swapper/0:    1]   lv : [ 800000], volt = 750000 uV (0 %) 
<6>[    0.568150]  [7:      swapper/0:    1] Trying to unpack rootfs image as initramfs...
*/
		for (j = 0; j < fvmap_header[i].num_of_lv; j++) {
			
			new->table[j].rate = old->table[j].rate;
			new->table[j].volt = old->table[j].volt;
			
		}

		for (j = 0; j < fvmap_header[i].num_of_pll; j++) {
			clks = sram_base + fvmap_header[i].o_members;
			plls = sram_base + clks->addr[j];
			clk_node = cmucal_get_node(vclk->list[j]);
			if (clk_node == NULL)
				continue;
			paddr_offset = clk_node->paddr & 0xFFFF;
			fvaddr_offset = plls->addr & 0xFFFF;
			if (paddr_offset == fvaddr_offset)
				continue;

			clk_node->paddr += fvaddr_offset - paddr_offset;
			clk_node->pll_con0 += fvaddr_offset - paddr_offset;
			if (clk_node->pll_con1)
				clk_node->pll_con1 += fvaddr_offset - paddr_offset;
		}
	}
}

int fvmap_init(void __iomem *sram_base)
{
	void __iomem *map_base;

	map_base = kzalloc(FVMAP_SIZE, GFP_KERNEL);

	fvmap_base = map_base;
	sram_fvmap_base = sram_base;
	pr_info("%s:fvmap initialize %pK\n", __func__, sram_base);
	fvmap_copy_from_sram(map_base, sram_base);

	return 0;
}
