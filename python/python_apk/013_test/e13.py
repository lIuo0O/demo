import kivy

from kivy.app import App
from kivy.uix.widget import Widget
from kivy.input.shape import ShapeRect

class MyW(Widget):

    def on_touch_move(self, touch):
        if 'pos' in touch.profile:
            self.ids.button1.pos = touch.pos

        if isinstance(touch.shape, ShapeRect):
            self.ids.label1.text = 'My touch have a rectangle shape of size' + str(touch.shape.width) + str(touch.shape.height);


class e13App(App):

    def build(self):
        return MyW();

if __name__ == "__main__":
    e13App().run();
