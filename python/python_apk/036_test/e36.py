from kivy.app import App
from kivy.lang import Builder
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.screenmanager import Screen


class MButton(Button):
    pass;

class MyW(BoxLayout):

    def __init__(self, **kwargs):
        super(MyW, self).__init__(**kwargs)
        s = Screen(name='hello1');
        s.add_widget(Label(text='src1'));
        self.ids.sm.add_widget(s);

        s = Screen(name='hello2');
        s.add_widget(Label(text='src2'));
        self.ids.sm.add_widget(s);

        self.ids.buttons.add_widget(MButton(text='hello1'));
        self.ids.buttons.add_widget(MButton(text='hello2'));

class e36App(App):

    def build(self):
        return MyW();

if __name__ == "__main__":
    e36App().run();
