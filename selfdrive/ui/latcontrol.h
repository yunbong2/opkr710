#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "common/params.h"
#include "ui.hpp"


bool control_button_clicked(int touch_x, int touch_y) {
  if (touch_x >= 1585 && touch_x <= 1725) {
    if (touch_y >= 905 && touch_y <= 1045) {
      return true;
    }
  }
  return false;
}

static void draw_control_button(UIState *s, int touch_x, int touch_y) {
  if (s->vision_connected){
    int btn_w = 140;
    int btn_h = 140;
    int btn_x = 1920 - btn_w - 195;
    int btn_y = 1080 - btn_h - 35;
    int btn_xc = btn_x + (btn_w/2);
    int btn_yc = btn_y + (btn_h/2);
    nvgBeginPath(s->vg);
    nvgRoundedRect(s->vg, btn_x, btn_y, btn_w, btn_h, 100);
    nvgStrokeColor(s->vg, nvgRGBA(255,255,255,80));
    nvgStrokeWidth(s->vg, 6);
    nvgStroke(s->vg);

    nvgFontSize(s->vg, 50);
    int latControl_read = read_param(&s->lateral_control, "LateralControlMethod");
    if (latControl_read == 2) {
      NVGcolor fillColor = nvgRGBA(255,0,0,150);
      nvgFillColor(s->vg, fillColor);
      nvgFill(s->vg);
      nvgFillColor(s->vg, nvgRGBA(255,255,255,200));
    } else {
      nvgFillColor(s->vg, nvgRGBA(255, 255, 255, 200));
    }
    nvgText(s->vg,btn_xc,btn_yc,"LQR",NULL);
  }
}

bool latcontrol( UIState *s, int touch_x, int touch_y ) {

  bool touched = false;
  
  draw_control_button(s, touch_x, touch_y);

  if (control_button_clicked(touch_x,touch_y)) {
    Params().write_db_value("LateralControlMethod", "2", 1);
    touched = true;
  }
  
  return touched;
}