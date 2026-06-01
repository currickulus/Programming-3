#include <gtkmm.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <vector>

class CountWindow : public Gtk::Window {
public:
    CountWindow() {
        set_title("Rainbow Counting 1 ↔ 20");
        fullscreen();
        
        override_background_color(Gdk::RGBA("black"));
        
        m_label.set_text("1");
        Pango::FontDescription font;
        font.set_size(290 * Pango::SCALE);
        font.set_weight(Pango::WEIGHT_BOLD);
        font.set_family("Sans");
        m_label.override_font(font);
        
        // Exit button
        m_btn_exit.set_label("✕ Exit");
        m_btn_exit.set_halign(Gtk::ALIGN_END);
        m_btn_exit.set_valign(Gtk::ALIGN_START);
        m_btn_exit.set_margin_top(20);
        m_btn_exit.set_margin_right(20);
        
        m_btn_exit.signal_clicked().connect(sigc::mem_fun(*this, &CountWindow::on_exit_clicked));
        
        m_box.set_orientation(Gtk::ORIENTATION_VERTICAL);
        m_box.pack_start(m_label, Gtk::PACK_EXPAND_WIDGET);
        m_box.pack_start(m_btn_exit, Gtk::PACK_SHRINK);
        
        add(m_box);
        show_all();
        
        signal_key_press_event().connect(sigc::mem_fun(*this, &CountWindow::on_key_press));
        
        m_thread = std::thread(&CountWindow::counting_thread, this);
    }

    ~CountWindow() {
        stop_thread_safely();
    }

private:
    Gtk::Box m_box{Gtk::ORIENTATION_VERTICAL};
    Gtk::Label m_label;
    Gtk::Button m_btn_exit;

    std::thread m_thread;

    std::atomic<bool> m_running{true};
    std::atomic<int>  m_current{1};
    std::atomic<int>  m_color_index{0};
    std::atomic<bool> m_counting_up{true};

    std::mutex m_state_mutex;

    // Improved ROYGBIV colors using hex (more accurate)
    const std::vector<std::string> m_colors = {
        "#FF0000",  // Red
        "#FF7F00",  // Orange
        "#FFFF00",  // Yellow
        "#00FF00",  // Green
        "#0000FF",  // Blue
        "#4B0082",  // Indigo (deep purple-blue)
        "#8F00FF"   // True Violet / Purple
    };

    void safe_update_label(int number, int color_idx) {
        Glib::signal_idle().connect_once([this, number, color_idx]() {
            if (m_running) {
                m_label.set_text(std::to_string(number));
                m_label.override_color(Gdk::RGBA(m_colors[color_idx % 7]));
            }
        });
    }

    void counting_thread() {
        while (m_running) {
            int current = m_current.load();
            int color_idx = m_color_index.load();
            
            safe_update_label(current, color_idx);

            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            std::lock_guard<std::mutex> lock(m_state_mutex);

            if (m_counting_up) {
                if (current < 20) m_current.fetch_add(1);
                else m_counting_up = false;
            } else {
                if (current > 1) m_current.fetch_sub(1);
                else m_counting_up = true;
            }

            m_color_index.fetch_add(1);
        }
    }

    void stop_thread_safely() {
        m_running = false;
        if (m_thread.joinable()) m_thread.join();
    }

    void on_exit_clicked() {
        close();
    }

    bool on_key_press(GdkEventKey* event) {
        if (event->keyval == GDK_KEY_q || event->keyval == GDK_KEY_Q) {
            close();
            return true;
        }
        return false;
    }
};

int main(int argc, char* argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.example.rainbowcount");
    CountWindow window;
    return app->run(window);
}
