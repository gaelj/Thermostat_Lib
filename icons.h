#ifndef ICONS_H
#define ICONS_H

#include <Arduino.h>

static char* empty_icon =
"\x18\x03" // Header: image_size_x(in pixels),imgage_size_y(in rows, 8-pixel blocks)
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

static char* flame_icon =
"\x18\x03"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xe0\xfe\xfc\xf0\xc0\x00\xe0\x80\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\xe0\xfd\xff\xfc\xff\xff\xff\xff\x3f\xff\xff\xff\xff\xfe\xf8\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x0f\x3f\x7f\x7f\x87\x01\x07\x01\x00\x00\xe3\x7f\x3f\x1f\x07\x00\x00\x00\x00";

static char* snow_icon =
"\x18\x03"
"\x00\x00\x40\x80\x80\xe0\xf0\x00\x00\x08\x18\x10\xff\x10\x18\x08\x00\x00\xf0\x80\x80\x80\x40\x00"
"\x00\x00\x44\x44\xc7\x83\x83\x82\xc6\x64\x28\x38\xff\x38\x28\x6c\xc6\x82\x83\x83\xc7\x44\x44\x00"
"\x00\x00\x04\x02\x03\x0f\x1f\x00\x00\x20\x30\x10\xff\x10\x30\x20\x00\x00\x1f\x03\x03\x02\x04\x00";

static char* absent_icon =
"\x18\x03"
"\x00\x00\x70\x70\x80\xc0\xe0\xe0\xf0\xf8\xf0\xe0\xe0\xc0\x80\x00\x00\x00\x00\x80\x80\xc0\x80\x80"
"\x00\x02\xfe\xff\xff\xff\xff\x1f\x1f\x1f\x0f\x03\xe1\xf5\xfa\xfa\xfd\x01\x01\x01\x01\x03\x03\x01"
"\x00\x00\x3f\x3f\x3f\x3f\x3f\x00\x00\x00\x00\x00\x3f\x3f\x3f\x3f\x3f\x00\x00\x00\x00\x00\x00\x00";

static char* moon_icon =
"\x18\x03"
"\x00\x80\xe0\xf0\xf8\xfc\xfc\x3e\x0e\x06\x03\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x38\xff\xff\xff\xff\xff\xf9\xc0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x03\x0f\x1f\x3f\x7f\x7f\xff\xff\xfe\xfc\xf8\xf8\xf0\xf0\xf0\xf0\xf0\x70\x70\x38\x18\x0c\x06";

static char* sun_icon =
"\x18\x03"
"\x00\x00\x40\x80\x80\x00\x04\x1c\x30\x80\xc0\xc0\xdf\xc0\xc0\x80\xa0\x18\x04\x00\x80\x80\x40\x00"
"\x10\x10\x10\x10\x11\x01\x38\xfe\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x7c\x01\x01\x10\x10\x10"
"\x00\x00\x04\x02\x02\x01\x40\x70\x19\x03\x07\x07\xf7\x07\x07\x03\x0b\x31\x40\x01\x03\x02\x04\x00";

static char* hot_icon =
"\x18\x03"
"\x00\x00\x00\x00\x00\x00\x04\x0c\xf8\x60\x00\x00\x0c\xfc\xf0\x00\x00\x04\x1c\xf8\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\xe0\x78\x0e\x03\x00\xc0\xf8\x1e\x07\x01\x80\xf0\x3c\x0f\x03\x00\x00\x00\x00"
"\x00\x40\xe0\xe0\xe0\xef\xec\xe0\xe0\xe0\xe7\xee\xe0\xe0\xe0\xe7\xef\xe8\xe0\xe0\xe0\xe0\xe0\x40";

static char* up_icon =
"\x18\x03"
"\x00\x00\x00\x00\x00\xc0\xf8\xf8\xfc\xff\xff\xff\xff\xff\xfe\xfc\xf8\xf0\xc0\x80\x00\x00\x00\x00"
"\x00\x00\x3c\x3f\x7f\x7f\x7f\x3f\x1f\xff\xff\xff\xff\xff\xff\x0f\x3f\x7f\x7f\x7f\x3f\x3e\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00";

static char* down_icon =
"\x18\x03"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x7c\xfc\xfe\xfe\xfe\xfc\xf0\xff\xff\xff\xff\xff\xff\xf8\xfc\xfe\xfe\xfe\xfc\x3c\x00\x00"
"\x00\x00\x00\x00\x01\x03\x0f\x1f\x3f\x7f\xff\xff\xff\xff\xff\x3f\x1f\x1f\x03\x00\x00\x00\x00\x00";

#endif // ICONS_H
