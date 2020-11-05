#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>


#define LAT_CONTROL_STAT 0

int latControl = LAT_CONTROL_STAT;

bool control_button_clicked(int touch_x, int touch_y) {
  if (touch_x >= 1660 && touch_x <= 1810) {
    if (touch_y >= 885 && touch_y <= 1035) {
      return true;
    }
  }
  return false;
}

static void draw_control_button(UIState *s, int touch_x, int touch_y) {
  if (s->vision_connected){

    if (latControl == LAT_CONTROL_STAT) {
      //draw_lock_button(s);
    }
    int btn_w = 140;
    int btn_h = 140;
    int btn_x = 1920 - btn_w - 200;
    int btn_y = 1080 - btn_h - 35;
    int btn_xc = btn_x + (btn_w/2);
    int btn_yc = btn_y + (btn_h/2);
    nvgBeginPath(s->vg);
    nvgRoundedRect(s->vg, btn_x, btn_y, btn_w, btn_h, 100);
    nvgStrokeColor(s->vg, nvgRGBA(255,255,255,80));
    nvgStrokeWidth(s->vg, 6);
    nvgStroke(s->vg);

    nvgFontSize(s->vg, 52);
    if (captureState == CAPTURE_STATE_CAPTURING) {
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

  if (control_button_clicked(touch_x,touch_y)) {}
  
  return touched;
}