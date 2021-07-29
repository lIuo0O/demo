import kivy

from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.button import Button

class MyW(Widget):
    def on_touch_down(self, touch):
        self.add_widget(Button(text=str(touch.pos), pos=touch.pos));
        if touch.is_double_tap:
            try:    
                self.remove_widget(self.ids.label1);
            except Exception as e:
                print(e);
        if touch.is_triple_tap:
            self.clear_widgets();

class e25App(App):
    def build(self):
        return MyW();

if __name__ == "__main__":
    e25App().run();
