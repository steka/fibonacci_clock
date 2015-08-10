#include <pebble.h>
#include "main.h"

#define USE_FIXED_TIME_FOR_PUBLISHING_IMAGE 0

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_30_black;
static Layer *s_fibo_layer;
static TextLayer *s_time_layer;
static Layer *s_charge_layer;
static Layer *s_arc5x5_layer;
static Layer *s_arc3x3_layer;
static Layer *s_arc2x2_layer;
static Layer *s_arc1x1L_layer;
static Layer *s_arc1x1R_layer;
static Layer *s_bluetooth_layer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif

  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  // s_fibo_layer
  s_fibo_layer = layer_create(GRect(19, 1, 105, 165));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_fibo_layer);

  // s_time_layer
  s_time_layer = text_layer_create(GRect(0, 65, 144, 40));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text(s_time_layer, "10:30");
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  text_layer_set_font(s_time_layer, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_time_layer);

  // s_charge_layer
  s_charge_layer = layer_create(GRect(127, 142, 15, 22));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_charge_layer);

  // s_arc5x5_layer
  s_arc5x5_layer = layer_create(GRect(21, 63, 101, 101));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_arc5x5_layer);

  // s_arc3x3_layer
  s_arc3x3_layer = layer_create(GRect(21, 3, 61, 61));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_arc3x3_layer);

  // s_arc2x2_layer
  s_arc2x2_layer = layer_create(GRect(81, 3, 41, 41));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_arc2x2_layer);

  // s_arc1x1L_layer
  s_arc1x1L_layer = layer_create(GRect(81, 43, 21, 21));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_arc1x1L_layer);

  // s_arc1x1R_layer
  s_arc1x1R_layer = layer_create(GRect(101, 43, 21, 21));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_arc1x1R_layer);

  // s_bluetooth_layer
  s_bluetooth_layer = layer_create(GRect(0, 141, 18, 22));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bluetooth_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  layer_destroy(s_fibo_layer);
  text_layer_destroy(s_time_layer);
  layer_destroy(s_charge_layer);
  layer_destroy(s_arc5x5_layer);
  layer_destroy(s_arc3x3_layer);
  layer_destroy(s_arc2x2_layer);
  layer_destroy(s_arc1x1L_layer);
  layer_destroy(s_arc1x1R_layer);
  layer_destroy(s_bluetooth_layer);
}
// END AUTO-GENERATED UI CODE

#if 1
  // GRects (Vertical)
  static struct GRect s_3x3_square  = {{ 2,  2}, { 61,  61}}; // 3x3 Square
  static struct GRect s_2x2_square  = {{62,  2}, { 41,  41}}; // 2x2 Square
  static struct GRect s_1x1L_square = {{62, 42}, { 21,  21}}; // 1x1 Square (left)
  static struct GRect s_1x1R_square = {{82, 42}, { 21,  21}}; // 1x1 Square (right)
  static struct GRect s_5x5_square  = {{ 2, 62}, {101, 101}}; // 5x5 Square
  static struct GRect s_outline     = {{ 0,  0}, {105, 165}};
#elif 0
  // GRects (Vertical)  (WARNING! coordinates are for the OLD layer position/size, replaced by above)
  static struct GRect s_3x3_square  = {{ 21,  3}, { 61,  61}}; // 3x3 Square
  static struct GRect s_2x2_square  = {{ 81,  3}, { 41,  41}}; // 2x2 Square
  static struct GRect s_1x1L_square = {{ 81, 43}, { 21,  21}}; // 1x1 Square (left)
  static struct GRect s_1x1R_square = {{101, 43}, { 21,  21}}; // 1x1 Square (right)
  static struct GRect s_5x5_square  = {{ 21, 63}, {101, 101}}; // 5x5 Square
  static struct GRect s_outline     = {{ 19,  1}, {105, 165}};
#else
  // GRects (Horizontal)  (WARNING! coordinates are for the OLD layer position/size)
  static struct GRect s_3x3_square  = {{ 3,  75}, { 52,  52}}; // 3x3 Square
  static struct GRect s_2x2_square  = {{ 3,  41}, { 35,  35}}; // 2x2 Square
  static struct GRect s_1x1L_square = {{ 37, 58}, { 18,  18}}; // 1x1 Square (bottom)
  static struct GRect s_1x1R_square = {{ 37, 41}, { 18,  18}}; // 1x1 Square (top)
  static struct GRect s_5x5_square  = {{ 54, 41}, { 86,  86}}; // 5x5 Square
  static struct GRect s_outline     = {{  1, 39}, {141,  90}};
#endif

// GBitmap
static GBitmap *s_battery_image;
static GBitmap *s_charging_image;
static GBitmap *s_plugged_image;
static GBitmap *s_bluetooth_image;
static GBitmap *s_cross_image;

// Global time
static int s_curr_hour;
static int s_curr_min;

// Settings
enum {  // DON'T CHANGE THE ORDER OF THESES!!!
  ConfShowTime = 1,
  ConfShowDate,
  ConfShowMonth,
  ConfShowWeekNum,
  ConfShowCharge,
  ConfShowBluetooth,
  ConfShowSpiral,
  ConfHourColor,
  ConfMinuteColor,
  ConfHourMinuteColor,
  ConfNoneColor,
  ConfSpiralColor,
  ConfBackgroundColor,
  ConfGridColor,
  ConfDotColor,
  ConfTimeColor,
  ConfOutlineColor,
  ConfVibeBluetooth,
  ConfShowTimeOnTap // Does not come from config page as separate key (included in ConfShowTime)
};

static struct {
  bool showTime;
  bool showTimeOnTap;
  bool showDate;
  bool showMonth;
  bool showWeekNum;
  bool showCharge;
  bool showBluetooth;
  bool vibeBluetooth;
  bool showSpiral;
  GColor hourColor;
  GColor minuteColor;
  GColor hourMinuteColor;
  GColor noneColor;
  GColor spiralColor;
  GColor backgroundColor;
  GColor gridColor;
  GColor dotColor;
  GColor timeColor;
  GColor outlineColor;
  bool legibleText; // Use legible color instead of timeColor
} conf = {  // Set up default value
  .showTime        = false,
  .showTimeOnTap = false,
  .showDate        = false,
  .showMonth       = false,
  .showWeekNum     = false,
  .showCharge      = true,
  .showBluetooth   = true,
  .vibeBluetooth   = true,
  .showSpiral      = true,
  .hourColor       = {.argb = GColorRedARGB8},
  .minuteColor     = {.argb = GColorGreenARGB8},
  .hourMinuteColor = {.argb = GColorBlueARGB8},
  .noneColor       = {.argb = GColorWhiteARGB8},
  .spiralColor     = {.argb = GColorChromeYellowARGB8},
  .backgroundColor = {.argb = GColorBlackARGB8},
  .gridColor       = {.argb = GColorBlackARGB8},
  .dotColor        = {.argb = GColorWhiteARGB8},
  .timeColor       = {.argb = GColorPictonBlueARGB8},
  .outlineColor    = {.argb = GColorDarkGrayARGB8},
  .legibleText = true,
};

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static void update_time() {
  // Create a long-lived buffer
  static char time_str[] = "hh:mm";

  // Write the current hours and minutes into the buffer
  clock_copy_time_string(time_str, sizeof(time_str));

#if USE_FIXED_TIME_FOR_PUBLISHING_IMAGE
  strcpy(time_str, "10:30");
#endif

  // Update current time on the TextLayer
  text_layer_set_text_color(s_time_layer, conf.timeColor);
  text_layer_set_text(s_time_layer, time_str);

  layer_set_hidden(text_layer_get_layer(s_time_layer), !conf.showTime);

  layer_mark_dirty(s_fibo_layer);
}

static void draw_spiral_arc(GContext *ctx, GPoint center, uint16_t radius ) {
  graphics_context_set_stroke_color(ctx, conf.spiralColor);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_draw_circle(ctx, center, radius - 2);
}

static void arc3x3_layer_update_callback(Layer *layer, GContext *ctx) {
  GRect bound = layer_get_frame(layer);
  draw_spiral_arc(ctx, GPoint(bound.size.w, bound.size.h), bound.size.w);
}

static void arc2x2_layer_update_callback(Layer *layer, GContext *ctx) {
  GRect bound = layer_get_frame(layer);
  draw_spiral_arc(ctx, GPoint(0, bound.size.h), bound.size.w);
}

static void arc1x1L_layer_update_callback(Layer *layer, GContext *ctx) {
  GRect bound = layer_get_frame(layer);
  draw_spiral_arc(ctx, GPoint(bound.size.w, 0), bound.size.w);
}

static void arc1x1R_layer_update_callback(Layer *layer, GContext *ctx) {
  GRect bound = layer_get_frame(layer);
  draw_spiral_arc(ctx, GPoint(0, 0), bound.size.w);
}

static void arc5x5_layer_update_callback(Layer *layer, GContext *ctx) {
  GRect bound = layer_get_frame(layer);
  draw_spiral_arc(ctx, GPoint(bound.size.w, 0), bound.size.w);
}

static void bluetooth_layer_update_callback(Layer *layer, GContext *ctx) {
  bool connected = bluetooth_connection_service_peek();

  // Draw bluetooth icon
  graphics_context_set_compositing_mode(ctx, GCompOpSet);
  graphics_draw_bitmap_in_rect(ctx, s_bluetooth_image, gbitmap_get_bounds(s_bluetooth_image));

  // Draw cross if not connected
  if (!connected) {
    graphics_draw_bitmap_in_rect(ctx, s_cross_image, gbitmap_get_bounds(s_cross_image));
  }
}

static void fibo_layer_update_callback(Layer *layer, GContext *ctx) {
  GColor fill_color[4]; // None, Hour, Minute, Hr+Min
  int8_t fc1L = 0, fc1R = 0, fc2 = 0, fc3 = 0, fc5 = 0;
  int8_t h = s_curr_hour;
  int8_t m = s_curr_min / 5; // Since only values from 1-12 can be displayed

  fill_color[0] = conf.noneColor;
  fill_color[1] = conf.hourColor;
  fill_color[2] = conf.minuteColor;
  fill_color[3] = conf.hourMinuteColor;

#if USE_FIXED_TIME_FOR_PUBLISHING_IMAGE
  h = 10;
  m = 30 / 5;
#endif

  // Determine what fill color to use in each box
  if (h >= 5) { fc5  |= 0x01; h -= 5; }
  if (h >= 3) { fc3  |= 0x01; h -= 3; }
  if (h >= 2) { fc2  |= 0x01; h -= 2; }
  if (h >= 1) { fc1L |= 0x01; h -= 1; }
  if (h >= 1) { fc1R |= 0x01; h -= 1; }

  if (m >= 5) { fc5  |= 0x02; m -= 5; }
  if (m >= 3) { fc3  |= 0x02; m -= 3; }
  if (m >= 2) { fc2  |= 0x02; m -= 2; }
  if (m >= 1) { fc1R |= 0x02; m -= 1; }  // The order of these two lines have been swapped, intentionally
  if (m >= 1) { fc1L |= 0x02; m -= 1; }  // The order of these two lines have been swapped, intentionally

  // Draw the time boxes
  graphics_context_set_fill_color(ctx, fill_color[fc3]);
  graphics_fill_rect(ctx, s_3x3_square, 0, GCornerNone);
  graphics_context_set_fill_color(ctx, fill_color[fc2]);
  graphics_fill_rect(ctx, s_2x2_square, 0, GCornerNone);
  graphics_context_set_fill_color(ctx, fill_color[fc1L]);
  graphics_fill_rect(ctx, s_1x1L_square, 0, GCornerNone);
  graphics_context_set_fill_color(ctx, fill_color[fc1R]);
  graphics_fill_rect(ctx, s_1x1R_square, 0, GCornerNone);
  graphics_context_set_fill_color(ctx, fill_color[fc5]);
  text_layer_set_text_color(s_time_layer, conf.legibleText ? gcolor_legible_over(fill_color[fc5]): conf.timeColor);
  graphics_fill_rect(ctx, s_5x5_square, 0, GCornerNone);

  // Draw the grid
  graphics_context_set_stroke_color(ctx, conf.gridColor);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_draw_rect(ctx, s_3x3_square);
  graphics_draw_rect(ctx, s_2x2_square);
  graphics_draw_rect(ctx, s_1x1L_square);
  graphics_draw_rect(ctx, s_1x1R_square);
  graphics_draw_rect(ctx, s_5x5_square);

  // Draw the grid dots
  graphics_context_set_stroke_color(ctx, conf.dotColor);
  for (int16_t y = s_outline.origin.y + 2; y <= s_outline.origin.y + s_outline.size.h; y += s_1x1L_square.size.h - 1) {
    for (int16_t x = s_outline.origin.x + 2; x <= s_outline.origin.x + s_outline.size.w; x += s_1x1L_square.size.w - 1) {
      graphics_draw_pixel(ctx, GPoint(x, y));
    }
  }

  // Draw the outline
  graphics_context_set_stroke_color(ctx, conf.outlineColor);
  graphics_context_set_stroke_width(ctx, 1);
  graphics_draw_rect(ctx, s_outline);
}

static void charge_layer_update_callback(Layer *layer, GContext *ctx) {
  BatteryChargeState batChargeState = battery_state_service_peek();
  GColor charge_color = GColorClear;

  // Select color for battery charge
  if (batChargeState.charge_percent >= 60) charge_color = GColorGreen;
  else if (batChargeState.charge_percent >= 25) charge_color = GColorYellow;
  else charge_color = GColorRed;

  // Draw battery charge
  graphics_context_set_fill_color(ctx, charge_color);
  int h = (100 - batChargeState.charge_percent) / 5 + 1;
  graphics_fill_rect(ctx, GRect(3, h, 8, 21 - h), 0, GCornerNone);

  // Draw battery outline
  graphics_context_set_compositing_mode(ctx, GCompOpSet);
  graphics_draw_bitmap_in_rect(ctx, s_battery_image, gbitmap_get_bounds(s_battery_image));

  // Draw charging icon, if active
  if (batChargeState.is_charging) {
    graphics_draw_bitmap_in_rect(ctx, s_charging_image, gbitmap_get_bounds(s_charging_image));
  } else

  // Draw plugged icon, if active
  if (batChargeState.is_plugged) {
    graphics_draw_bitmap_in_rect(ctx, s_plugged_image, gbitmap_get_bounds(s_plugged_image));
  }
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  s_curr_hour = (tick_time->tm_hour > 12) ? tick_time->tm_hour - 12 : tick_time->tm_hour;
  s_curr_min = tick_time->tm_min;

  update_time();
}

static void battery_charge_handler(BatteryChargeState charge) {
  layer_mark_dirty(s_charge_layer);
}

static void bluetooth_handler(bool connected) {
  if (!connected && conf.vibeBluetooth) {
    vibes_short_pulse();
  }
  layer_mark_dirty(s_bluetooth_layer);
}

static void tap_handler(AccelAxisType axis, int32_t direction) {
  layer_set_hidden(text_layer_get_layer(s_time_layer), false);
}

static void load_config(void) {
  if (persist_exists(ConfShowTime)) {
    conf.showTime = persist_read_bool(ConfShowTime);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config showTime = %d", conf.showTime);
    layer_set_hidden(text_layer_get_layer(s_time_layer), !conf.showTime);
  }

  if (persist_exists(ConfShowTimeOnTap)) {
    conf.showTimeOnTap = persist_read_bool(ConfShowTimeOnTap);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config showTimeOnTap = %d", conf.showTimeOnTap);
    if (conf.showTimeOnTap) {
      accel_tap_service_subscribe(tap_handler);
//      APP_LOG(APP_LOG_LEVEL_INFO, "Subscribe tap");
    } else {
      accel_tap_service_unsubscribe();
//      APP_LOG(APP_LOG_LEVEL_INFO, "Unsubscribe tap");
    }
  }

  if (persist_exists(ConfShowDate)) {
    conf.showDate = persist_read_bool(ConfShowDate);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config showDate = %d", conf.showDate);
    // Todo
  }

  if (persist_exists(ConfShowMonth)) {
    conf.showMonth = persist_read_bool(ConfShowMonth);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config showMonth = %d", conf.showMonth);
    // Todo
  }

  if (persist_exists(ConfShowWeekNum)) {
    conf.showWeekNum = persist_read_bool(ConfShowWeekNum);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config showWeekNum = %d", conf.showWeekNum);
    // Todo
  }

  if (persist_exists(ConfShowCharge)) {
    conf.showCharge = persist_read_bool(ConfShowCharge);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config showCharge = %d", conf.showCharge);
    layer_set_hidden(s_charge_layer, !conf.showCharge);
  }

  if (persist_exists(ConfShowBluetooth)) {
    conf.showBluetooth = persist_read_bool(ConfShowBluetooth);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config showBluetooth = %d", conf.showBluetooth);
    layer_set_hidden(s_bluetooth_layer, !conf.showBluetooth);
  }

  if (persist_exists(ConfVibeBluetooth)) {
    conf.vibeBluetooth = persist_read_bool(ConfVibeBluetooth);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config vibeBluetooth = %d", conf.vibeBluetooth);
  }

  if (persist_exists(ConfShowSpiral)) {
    conf.showSpiral = persist_read_bool(ConfShowSpiral);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config showSpiral = %d", conf.showSpiral);
    layer_set_hidden(s_arc1x1L_layer, !conf.showSpiral);
    layer_set_hidden(s_arc1x1R_layer, !conf.showSpiral);
    layer_set_hidden(s_arc2x2_layer, !conf.showSpiral);
    layer_set_hidden(s_arc3x3_layer, !conf.showSpiral);
    layer_set_hidden(s_arc5x5_layer, !conf.showSpiral);
  }

  if (persist_exists(ConfHourColor)) {
    conf.hourColor.argb = persist_read_int(ConfHourColor);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config hourColor = %d", conf.hourColor.argb);
    layer_mark_dirty(s_fibo_layer);
  }

  if (persist_exists(ConfMinuteColor)) {
    conf.minuteColor.argb = persist_read_int(ConfMinuteColor);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config minuteColor = %d", conf.minuteColor.argb);
    layer_mark_dirty(s_fibo_layer);
  }

  if (persist_exists(ConfHourMinuteColor)) {
    conf.hourMinuteColor.argb = persist_read_int(ConfHourMinuteColor);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config hourMinuteColor = %d", conf.hourMinuteColor.argb);
    layer_mark_dirty(s_fibo_layer);
  }

  if (persist_exists(ConfNoneColor)) {
    conf.noneColor.argb = persist_read_int(ConfNoneColor);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config noneColor = %d", conf.noneColor.argb);
    layer_mark_dirty(s_fibo_layer);
  }

  if (persist_exists(ConfSpiralColor)) {
    conf.spiralColor.argb = persist_read_int(ConfSpiralColor);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config spiralColor = %d", conf.spiralColor.argb);
    layer_mark_dirty(s_arc1x1L_layer);
    layer_mark_dirty(s_arc1x1R_layer);
    layer_mark_dirty(s_arc2x2_layer);
    layer_mark_dirty(s_arc3x3_layer);
    layer_mark_dirty(s_arc5x5_layer);
  }

  if (persist_exists(ConfBackgroundColor)) {
    conf.backgroundColor.argb = persist_read_int(ConfBackgroundColor);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config backgroundColor = %d", conf.backgroundColor.argb);
    window_set_background_color(s_window, conf.backgroundColor);
  }

  if (persist_exists(ConfGridColor)) {
    conf.gridColor.argb = persist_read_int(ConfGridColor);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config gridColor = %d", conf.gridColor.argb);
    layer_mark_dirty(s_fibo_layer);
  }

  if (persist_exists(ConfDotColor)) {
    conf.dotColor.argb = persist_read_int(ConfDotColor);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config dotColor = %d", conf.dotColor.argb);
    layer_mark_dirty(s_fibo_layer);
  }

  if (persist_exists(ConfTimeColor)) {
    int value = persist_read_int(ConfTimeColor);
    conf.legibleText = (value == 256);
    conf.timeColor.argb = (uint8_t)(value & 0xFF);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config timeColor = %d", conf.timeColor.argb);
    update_time();
  }

  if (persist_exists(ConfOutlineColor)) {
    conf.outlineColor.argb = persist_read_int(ConfOutlineColor);
//    APP_LOG(APP_LOG_LEVEL_INFO, "Load config outlineColor = %d", conf.outlineColor.argb);
    layer_mark_dirty(s_fibo_layer);
  }
}

static void inbox_received_handler(DictionaryIterator *iterator, void *context) {
  Tuple *t = dict_read_first(iterator);

  while (t) {
//    if (t->type == TUPLE_CSTRING) {
//      APP_LOG(APP_LOG_LEVEL_INFO, "RxTuple %d:%s", (int)t->key, t->value->cstring);
//    } else {
//      APP_LOG(APP_LOG_LEVEL_INFO, "RxTuple (unknown type)");
//    }

    switch(t->key) {
      case ConfShowTime:
        switch (atoi(t->value->cstring)) {
          default:
          case 0: // Hide
            conf.showTime = false;
            conf.showTimeOnTap = false;
          break;
          case 1: // Show
            conf.showTime = true;
            conf.showTimeOnTap = false;
          break;
          case 2: // Show on tap
            conf.showTime = false;
            conf.showTimeOnTap = true;
          break;
        }
        persist_write_bool(t->key, conf.showTime);
        persist_write_bool(ConfShowTimeOnTap, conf.showTimeOnTap);
        layer_set_hidden(text_layer_get_layer(s_time_layer), !conf.showTime);
        if (conf.showTimeOnTap) {
          accel_tap_service_subscribe(tap_handler);
//          APP_LOG(APP_LOG_LEVEL_INFO, "Subscribe tap");
        } else {
          accel_tap_service_unsubscribe();
//          APP_LOG(APP_LOG_LEVEL_INFO, "Unsubscribe tap");
        }
        break;
      case ConfShowDate:
        conf.showDate = atoi(t->value->cstring);
        persist_write_bool(t->key, conf.showDate);
        // Todo
        break;
      case ConfShowMonth:
        conf.showMonth = atoi(t->value->cstring);
        persist_write_bool(t->key, conf.showMonth);
        // Todo
        break;
      case ConfShowWeekNum:
        conf.showWeekNum = atoi(t->value->cstring);
        persist_write_bool(t->key, conf.showWeekNum);
        // Todo
        break;
      case ConfShowCharge:
        conf.showCharge = atoi(t->value->cstring);
        persist_write_bool(t->key, conf.showCharge);
        layer_set_hidden(s_charge_layer, !conf.showCharge);
        break;
      case ConfShowBluetooth:
        conf.showBluetooth = atoi(t->value->cstring);
        persist_write_bool(t->key, conf.showBluetooth);
        layer_set_hidden(s_bluetooth_layer, !conf.showBluetooth);
        break;
      case ConfVibeBluetooth:
        conf.vibeBluetooth = atoi(t->value->cstring);
        persist_write_bool(t->key, conf.vibeBluetooth);
        break;
      case ConfShowSpiral:
        conf.showSpiral = atoi(t->value->cstring);
        persist_write_bool(t->key, conf.showSpiral);
        layer_set_hidden(s_arc1x1L_layer, !conf.showSpiral);
        layer_set_hidden(s_arc1x1R_layer, !conf.showSpiral);
        layer_set_hidden(s_arc2x2_layer, !conf.showSpiral);
        layer_set_hidden(s_arc3x3_layer, !conf.showSpiral);
        layer_set_hidden(s_arc5x5_layer, !conf.showSpiral);
        break;
      case ConfHourColor:
        conf.hourColor = (GColor){.argb = atoi(t->value->cstring)};
        persist_write_int(t->key, conf.hourColor.argb);
        layer_mark_dirty(s_fibo_layer);
        break;
      case ConfMinuteColor:
        conf.minuteColor = (GColor){.argb = atoi(t->value->cstring)};
        persist_write_int(t->key, conf.minuteColor.argb);
        layer_mark_dirty(s_fibo_layer);
        break;
      case ConfHourMinuteColor:
        conf.hourMinuteColor = (GColor){.argb = atoi(t->value->cstring)};
        persist_write_int(t->key, conf.hourMinuteColor.argb);
        layer_mark_dirty(s_fibo_layer);
        break;
      case ConfNoneColor:
        conf.noneColor = (GColor){.argb = atoi(t->value->cstring)};
        persist_write_int(t->key, conf.noneColor.argb);
        layer_mark_dirty(s_fibo_layer);
        break;
      case ConfSpiralColor:
        conf.spiralColor = (GColor){.argb = atoi(t->value->cstring)};
        persist_write_int(t->key, conf.spiralColor.argb);
        layer_mark_dirty(s_arc1x1L_layer);
        layer_mark_dirty(s_arc1x1R_layer);
        layer_mark_dirty(s_arc2x2_layer);
        layer_mark_dirty(s_arc3x3_layer);
        layer_mark_dirty(s_arc5x5_layer);
        break;
      case ConfBackgroundColor: {
        conf.backgroundColor = (GColor){.argb = atoi(t->value->cstring)};
        persist_write_int(t->key, conf.backgroundColor.argb);
        window_set_background_color(s_window, conf.backgroundColor);
        }  break;
      case ConfGridColor:
        conf.gridColor = (GColor){.argb = atoi(t->value->cstring)};
        persist_write_int(t->key, conf.gridColor.argb);
        layer_mark_dirty(s_fibo_layer);
        break;
      case ConfDotColor:
        conf.dotColor = (GColor){.argb = atoi(t->value->cstring)};
        persist_write_int(t->key, conf.dotColor.argb);
        layer_mark_dirty(s_fibo_layer);
        break;
      case ConfTimeColor: {
        int value = atoi(t->value->cstring);
        conf.legibleText = (value == 256);
        conf.timeColor = (GColor){.argb = (uint8_t)(value & 0xFF)};
        persist_write_int(t->key, value);
        update_time();
      } break;
      case ConfOutlineColor:
        conf.outlineColor = (GColor){.argb = atoi(t->value->cstring)};
        persist_write_int(t->key, conf.outlineColor.argb);
        layer_mark_dirty(s_fibo_layer);
        break;
    }
    t = dict_read_next(iterator);
  }
}

void show_main(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);

  // Set up layer callbacks
  layer_set_update_proc(s_fibo_layer, fibo_layer_update_callback);
  layer_set_update_proc(s_charge_layer, charge_layer_update_callback);
  layer_set_update_proc(s_arc3x3_layer, arc3x3_layer_update_callback);
  layer_set_update_proc(s_arc2x2_layer, arc2x2_layer_update_callback);
  layer_set_update_proc(s_arc1x1L_layer, arc1x1L_layer_update_callback);
  layer_set_update_proc(s_arc1x1R_layer, arc1x1R_layer_update_callback);
  layer_set_update_proc(s_arc5x5_layer, arc5x5_layer_update_callback);
  layer_set_update_proc(s_bluetooth_layer, bluetooth_layer_update_callback);

  // Create bitmaps
  s_battery_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY);
  s_charging_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CHARGING);
  s_plugged_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PLUGGED);
  s_bluetooth_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BLUETOOTH);
  s_cross_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CROSS);

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  // Register with BatteryStateService
  battery_state_service_subscribe(battery_charge_handler);

  // Register with BluetoothConnectionService
  bluetooth_connection_service_subscribe(bluetooth_handler);

  app_message_register_inbox_received((AppMessageInboxReceived) inbox_received_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  load_config();

  // Make sure that the currnet time is displayed from the start
  update_time();
}

void hide_main(void) {
  window_stack_remove(s_window, true);

  gbitmap_destroy(s_battery_image);
  gbitmap_destroy(s_charging_image);
  gbitmap_destroy(s_plugged_image);
  gbitmap_destroy(s_bluetooth_image);
  gbitmap_destroy(s_cross_image);

  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();
}

int main(void) {
  show_main();
  app_event_loop();
  hide_main();
}
