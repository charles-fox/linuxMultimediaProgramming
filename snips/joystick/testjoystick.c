// gcc joystick.c -o joystick
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/joystick.h>

int read_event(int fd, struct js_event *event) {
    ssize_t bytes;
    bytes = read(fd, event, sizeof(*event));
    if (bytes == sizeof(*event))
        return 0;
    return -1;
}
size_t get_axis_count(int fd) {
    __u8 axes;
    if (ioctl(fd, JSIOCGAXES, &axes) == -1)
        return 0;
    return axes;
}
size_t get_button_count(int fd) {
    __u8 buttons;
    if (ioctl(fd, JSIOCGBUTTONS, &buttons) == -1)
        return 0;
    return buttons;
}
struct axis_state {
    short x, y;
};
size_t get_axis_state(struct js_event *event, struct axis_state axes[3]) {
    size_t axis = event->number / 2;
    if (axis < 3)
    {
        if (event->number % 2 == 0)
            axes[axis].x = event->value;
        else
            axes[axis].y = event->value;
    }
    return axis;
}
int main(int argc, char *argv[])
{
    const char *device;
    int js;
    struct js_event event;
    struct axis_state axes[3] = {0};
    size_t axis;
    if (argc > 1)
        device = argv[1];
    else
        device = "/dev/input/js0";
    js = open(device, O_RDONLY);
    if (js == -1)
        perror("Could not open joystick");
    while (read_event(js, &event) == 0)
    {
        switch (event.type)
        {
            case JS_EVENT_BUTTON:
                printf("Button %u %s\n", event.number, event.value ? "pressed" : "released");
                break;
            case JS_EVENT_AXIS:
                axis = get_axis_state(&event, axes);
                if (axis < 3)
                    printf("Axis %zu at (%6d, %6d)\n", axis, axes[axis].x, axes[axis].y);
                break;
            default:   /* Ignore init events. */
                break;
        }
        fflush(stdout);
    }
    close(js);
    return 0;
}
