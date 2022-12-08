/**
 * @file Sprite.h
 * @brief Declaration and implementation of Sprite class- handles loading images for sprites
 *
 * @author
 * @bug
 */
#ifndef SPRITE_H
#define SPRITE_H

#include "Point.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Sprite {
  private:
   ALLEGRO_BITMAP* image;
   int width;
   int height;
   
  public:

   // x and y are the origin points of the bitmap
   // filename is where the image is located, must have set path
  Sprite(const char* filename) {
      image = al_load_bitmap(filename);
      width = al_get_bitmap_width(image);
      height = al_get_bitmap_height(image);
   }

   ~Sprite() {
      al_destroy_bitmap(image);
   }

   void drawToOrigin() {
      al_draw_bitmap(image, 0, 0, 0);
   }


   void lockBitmap(int f) {
      al_lock_bitmap(image, al_get_bitmap_format(image), f);
   }
   void unlockBitmap() {
      al_unlock_bitmap(image);
   }
   
   // draw image centred at parameter position
   // flags can be
   // ALLEGRO_FLIP_HORIZONTAL
   // ALLEGRO_FLIP_VERTICAL
   void draw(Point p, int f) {
      al_draw_bitmap(image, p.x - width/2, p.y - height/2, f);
   }
   
   void drawFore(Point p, int f){
      al_draw_bitmap(image, p.x, p.y, f);
   }

   // unique function to draw background images for parallax scrolling
   void draw_parallax_background(float x, int f) {
      al_draw_bitmap_region(image, x, 0,       // source x, y
			    width / 2, height, // source width, height
			    0, 0,              // destination x, y
			    f);                // flags
   }
   
   void draw_rotated(Point p, double angle, int f) {
      al_draw_rotated_bitmap(image, width / 2, height / 2,
				    p.x, p.y, angle, f);
   }

   
   
   void draw_tinted(Point p, ALLEGRO_COLOR c, int f) {
      al_draw_tinted_bitmap(image, c, p.x, p.y - height / 2, f);
   }
   
   void draw_tinted_scaled(Point p, ALLEGRO_COLOR c, int f) {
      // al_draw_tinted_scaled_bitmap( bitmap, color, sourcex, sourcey, source width,
      // source height, destination x, destination y, destination width, destination height,
      // flags);
      al_draw_tinted_scaled_bitmap(image, c, 0, 0, 290, 74, 
				   p.x, p.y - height / 2,
				   width / 5,
				   height / 5, f);
      
   }

   
   void setTarget() {
      al_set_target_bitmap(image);
   }
   
   
   void draw_death_anim(int c, Point p, int f) {
      al_draw_bitmap_region(image,
			    c * 118.0, 0.0,
			    118.0, 118.0,
			    p.x - 118.0 / 2,
			    p.y - 118.0 / 2, f);
   }
   void draw_menu_anim(int c, int f){
      al_draw_bitmap_region(image, 0.0, c*233.0, 592.0, 233.0, 104.0, 183.5, f);
   }
   
   void draw_region(int r, int c, float bw, float bh, Point destination, int f) {
      al_draw_bitmap_region(image,
			    c * bw, r * bh,
			    bw, bh,
			    destination.x - 47.0 / 2,
			    destination.y - 40.0 / 2, f);
   }
   void draw_lives(float bw, float bh, Point destination, int f){
      al_draw_bitmap_region(image, 0, 0, bw, bh, destination.x - 141 / 2, destination.y - 40 / 2, f);
	 }
   void draw_boss(int r, int c, float bw, float bh, Point destination, int f){
      al_draw_bitmap_region(image,
			    c * bw, r * bh,
			    bw, bh,
			    destination.x - 200.0 / 2,
			    destination.y - 200.0 / 2, f);
   }

   
};

#endif
