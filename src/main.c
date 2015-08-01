#include <pebble.h>

// Windows
static Window *s_main_window;

// Layers
static Layer *s_grid_layer;
static TextLayer *s_time_layer;
static Layer *s_charge_layer;

#if 1
  // GRects (Vertical)
  static struct GRect s_3x3_square  = {{ 21,  3}, { 61,  61}}; // 3x3 Square
  static struct GRect s_2x2_square  = {{ 81,  3}, { 41,  41}}; // 2x2 Square
  static struct GRect s_1x1L_square = {{ 81, 43}, { 21,  21}}; // 1x1 Square (left)
  static struct GRect s_1x1R_square = {{101, 43}, { 21,  21}}; // 1x1 Square (right)
  static struct GRect s_5x5_square  = {{ 21, 63}, {101, 101}}; // 5x5 Square
  static struct GRect s_outline     = {{ 19,  1}, {105, 165}};
#else
  // GRects (Horizontal)
  static struct GRect s_3x3_square  = {{ 3,  75}, { 52,  52}}; // 3x3 Square
  static struct GRect s_2x2_square  = {{ 3,  41}, { 35,  35}}; // 2x2 Square
  static struct GRect s_1x1L_square = {{ 37, 58}, { 18,  18}}; // 1x1 Square (bottom)
  static struct GRect s_1x1R_square = {{ 37, 41}, { 18,  18}}; // 1x1 Square (top)
  static struct GRect s_5x5_square  = {{ 54, 41}, { 86,  86}}; // 5x5 Square
  static struct GRect s_outline     = {{  1, 39}, {141,  90}};
#endif

// GBitmap
static GBitmap *s_spiral_image;
static GBitmap *s_battery_image;
static GBitmap *s_charging_image;
static GBitmap *s_plugged_image;
  
// Global time
static int s_curr_hour;
static int s_curr_min;

static void update_time() {
  // Create a long-lived buffer
  static char time_str[] = "hh:mm";

  // Write the current hours and minutes into the buffer
  clock_copy_time_string(time_str, sizeof(time_str));

  // Update current time on the TextLayer
  text_layer_set_text(s_time_layer, time_str);
}

static void grid_layer_update_callback(Layer *layer, GContext *ctx) {

  GColor fill_color[] = {GColorWhite, GColorRed, GColorGreen, GColorBlue};
  int8_t fc1L = 0, fc1R = 0, fc2 = 0, fc3 = 0, fc5 = 0;
  int8_t h = s_curr_hour;
  int8_t m = s_curr_min / 5; // Since only values from 1-12 can be displayed

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
  graphics_fill_rect(ctx, s_5x5_square, 0, GCornerNone);

  // Draw the grid
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_draw_rect(ctx, s_3x3_square);
  graphics_draw_rect(ctx, s_2x2_square);
  graphics_draw_rect(ctx, s_1x1L_square);
  graphics_draw_rect(ctx, s_1x1R_square);
  graphics_draw_rect(ctx, s_5x5_square);

  // Draw the grid dots
  graphics_context_set_stroke_color(ctx, GColorWhite);
  for (int16_t y = s_outline.origin.y + 2; y <= s_outline.origin.y + s_outline.size.h; y += s_1x1L_square.size.h - 1) {
    for (int16_t x = s_outline.origin.x + 2; x <= s_outline.origin.x + s_outline.size.w; x += s_1x1L_square.size.w - 1) {
      graphics_draw_pixel(ctx, GPoint(x, y));
    }
  }
  
  // Draw spiral
  graphics_context_set_compositing_mode(ctx, GCompOpSet);
  graphics_draw_bitmap_in_rect(ctx, s_spiral_image, gbitmap_get_bounds(s_spiral_image));
  
  // Draw the outline
  graphics_context_set_stroke_color(ctx, GColorDarkGray);
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

static void main_window_load(Window *window) {
  // Get windows root layer and its bounds
  Layer *root_layer = window_get_root_layer(window);
  GRect root_bounds = layer_get_frame(root_layer);

  // Create the grid layer
  s_grid_layer = layer_create(root_bounds);
  layer_set_update_proc(s_grid_layer, grid_layer_update_callback);

  // Add it as a child layer to the Window's root layer
  layer_add_child(root_layer, s_grid_layer);

  // Create time TextLayer
  s_time_layer = text_layer_create(GRect(root_bounds.origin.x, 65, root_bounds.size.w, 40));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);

  // Improve the layout to be more like a watchface
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(root_layer, text_layer_get_layer(s_time_layer));

  // Create charge layer
  s_charge_layer = layer_create(GRect(127, 142, 15, 22));
  layer_set_update_proc(s_charge_layer, charge_layer_update_callback);

  // Add it as a child layer to the Window's root layer
  layer_add_child(root_layer, s_charge_layer);
  
  // Createing bitmaps
  s_spiral_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SPIRAL);
  s_battery_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BATTERY);
  s_charging_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CHARGING);
  s_plugged_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PLUGGED);
  
  // Make sure that the currnet time is displayed from the start
  update_time();
}

static void main_window_unload(Window *window) {
  gbitmap_destroy(s_plugged_image);
  gbitmap_destroy(s_charging_image);
  gbitmap_destroy(s_battery_image);
  gbitmap_destroy(s_spiral_image);
  layer_destroy(s_charge_layer);
  text_layer_destroy(s_time_layer);
  layer_destroy(s_grid_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();

  s_curr_hour = (tick_time->tm_hour > 12) ? tick_time->tm_hour - 12 : tick_time->tm_hour;
  s_curr_min = tick_time->tm_min;

  layer_mark_dirty(s_grid_layer);
}

void battery_charge_handler(BatteryChargeState charge) {
  layer_mark_dirty(s_charge_layer);
}

void init(void) {
  // Create main Window element and assign to pointer
  s_main_window = window_create();
  window_set_background_color(s_main_window, GColorBlack);

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated = true
  window_stack_push(s_main_window, true);

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  // Register with BatteryStateService
  battery_state_service_subscribe(battery_charge_handler);
}

void deinit(void) {
  battery_state_service_unsubscribe();
  tick_timer_service_unsubscribe();
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
