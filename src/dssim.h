/*
 *  dssim.h
 *  dssim
 *
 *  Created by porneL on 22.lut.11.
 *
 */

#ifndef DSSIM_H
#define DSSIM_H

#include <wand/MagickWand.h>

typedef struct dssim_info dssim_info;

dssim_info *dssim_init(void);

void dssim_dealloc(dssim_info *inf);

void dssim_set_original(dssim_info *, PixelPacket *, const int width, const int height, double gamma);
int  dssim_set_modified(dssim_info *, PixelPacket *, const int width, const int height, double gamma);

double dssim_compare(dssim_info *inf, float **ssimmap);

#endif

