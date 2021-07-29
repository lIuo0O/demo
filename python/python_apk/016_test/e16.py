from kivy.app import App

from kivy.uix.widget import Widget
from kivy.uix.button import Button
from kivy.graphics import Color, Ellipse, Line
from kivy.gesture import Gesture, GestureDatabase

gdb = GestureDatabase();

check  = gdb.str_to_gesture('eNq1l0tuI0cMhvd9EXsTofgmL6BsA\
gAgcYWb\GMmtmBpksztwyY1kgZI0rNpbdr+u+pjkX+9+v718+uf3zbP++Pp68d++v\
X8PIzp/ukA08Pd2+6P/d10wPwzHzQdH+6Op4/3z/tj/svT/ZeDTPf/Cnm\
oZtNBZ5Rl/8P769tp7uZzt/iPbr/NraYD9AjmIXzLLoDTdmxgBLsSMMIw\
5OHzcP6eX9O0/WVsCMFGmCuaGgjBdPy0+/8wXGFkeu4Ig7LzgISbMw/j6\
fh8hmMMBDIkdBYPimV4pQ7W8EQMUA4LMhMzCyW5watKgJoOHhxsuIz3ws\
cVb8ExhpIxDoIgvcEzhoaiZ1geA20Rj+UAwlp4LDxd8OkqO4KHYXLI4oY\
OwEai4oPRmHiZXr6iXOiY9mXBFUNYacAVDm4uIOCiaXws24plK9oq7PIU\
r56iOqsyg+acyOrezJicpTCI3YYy5HtapFNZSldLCcRgCCk4hqniDZ2dH\
ZjCMf1EXh47laNEN2MfEjkzJFgtK3BLHwEAGTcnlSu7LNPLUbo6+n2m5G\
bAuVzUr/ShYQzoSBSWi5iXJwyVqWRr4ctX+om1mq+GR7ibAA8dJuHLfC5\
nGVbjl7dMS/tk1g3tB3OXZyWXsyyrsMtWtlXY5SnHGmwpPwW+s3M15h5C\
kVvM8FyWcWH3Uce5io00A/8Eu7wUWoVdXoqswi4v5eIlseTWl6e9Cqh6+\
IUt6OoUwAJD88KwjC4rJVZAazmpsAa6jFRaA10+qqyBLht1DRu1bNQ1bL\
Sy0S425mWFOc9khtxcnRwuaEW6PZnH8sFp5aPRKuwy0i5GMnsmHJE32dz\
73a5oG3nJgLyemqDgXKtPu/m2//ix379d7u6m8+XdbLrf5jg2Y9picD5O\
B/NpN4vQIrYYLWKJHiX6aJFblBahRSvRvEUsETuQjRapxe6uHSjPsBK7u\
0CL0mKUyLKJ25/NLbRaUI+PzwGsRWrxzOr0qKNy5+ydHnVUzsftj7JFdK\
7cAUSrW3SugrdpReeqdluV6Fxdu6hdv6hcCeYabQl7KFG5ElWpiM6itqg\
tWovWorXYlU6/d234y/71+eWUVud1dRvz2xT/en06vcwfWiP7QFU51dP7\
l/3H7u1xX2+gP9F+/MHc7jw1fz98vD99fTxV65yN6YfP81jE8nDMa8j81\
bD5B2R9zCo=')

def simplegesture(name, point_list):
    g = Gesture();
    g.add_stroke(point_list);
    g.normalize();
    g.name = name;
    return g;

class GestureBoard(Widget):

    def __init__(self, *args, **kwargs):
        super(GestureBoard, self).__init__();
        self.gdb = GestureDatabase();
        self.gdb.add_gesture(check);

    def on_touch_down(self, touch):
        userdata = touch.ud;
        with self.canvas:
            Color(1, 1, 0);
            d = 30.0;
            Ellipse(pos=(touch.x - d/2, touch.y - d/2),
                    size=(d, d)) 
            userdata['line'] = Line(points=(touch.x, touch.y));
        return True;
    
    def on_touch_move(self, touch):
        try:
            touch.ud['line'].points += [touch.x, touch.y]
            return True;
        except (KeyError) as e:
            pass

    def on_touch_up(self, touch):
        g = simplegesture('', list(zip(touch.ud['line'].points[::2], touch.ud['line'].points[1::2])));
        print("gesture representation:", self.gdb.gesture_to_str(g));
        print("check:", g.get_score(check));
        g2 = self.gdb.find(g, minscore=0.70);
        print(g2);
        if g2:
            if g2[1] == check:print("check");
            self.canvas.clear();

class e16App(App):
    
    def build(self):
        return GestureBoard();


if __name__ == "__main__":
    e16App().run();
