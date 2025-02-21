#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WServer.h>
#include <Wt/Chart/WCartesianChart.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WTimer.h>
#include <Wt/WAbstractItemView.h>
#include <Wt/WItemDelegate.h>
#include <cmath>

class MyApplication : public Wt::WApplication {
public:
    MyApplication(const Wt::WEnvironment& env)
        : Wt::WApplication(env) {
        setTitle("GOVNO");

        // Создаем контейнер для размещения виджетов
        Wt::WContainerWidget* container = root();

        // Добавляем поле ввода
        inputField_ = container->addWidget(std::make_unique<Wt::WLineEdit>());

        Wt::WPushButton* button = container->addWidget(std::make_unique<Wt::WPushButton>("Upd graph"));
        button->clicked().connect(this, &MyApplication::updateChart);

        chart_ = container->addWidget(std::make_unique<Wt::Chart::WCartesianChart>());
        chart_->setTitle("y = x - z");
        chart_->setType(Wt::Chart::ChartType::Scatter);
        chart_->setXSeriesColumn(0);
        chart_->setLegendEnabled(false);

        // Создание модели данных для графика
        model_ = std::make_shared<Wt::WStandardItemModel>(101, 2);

        updateChart(); // Инициализация графика

    }

private:
    void updateChart() {
        // Получение значения z из поля ввода
        double z = 0.0;

        // Получение значения z из поля ввода и обработка ошибок
        try {
            std::string zText = inputField_->text().toUTF8();
            if (!zText.empty()) {
                z = std::stod(zText);
            }
        }
        catch (const std::invalid_argument& e) {
            z = 0.0; // Значение по умолчанию в случае ошибки
            std::cerr << "Invalid input for z: " << e.what() << std::endl;
        }
        catch (const std::out_of_range& e) {
            z = 0.0; // Значение по умолчанию в случае ошибки
            std::cerr << "Input for z is out of range: " << e.what() << std::endl;
        }

        // Заполнение модели данными
        for (unsigned i = 0; i <= 100; ++i) {
            double x = static_cast<double>(i) - 50;
            double y = x - z;

            model_->setData(i, 0, x);
            model_->setData(i, 1, y);
        }

        // Обновление графика с новыми данными
        chart_->setModel(model_);
        chart_->axis(Wt::Chart::Axis::X).setLocation(Wt::Chart::AxisValue::Zero);
        chart_->axis(Wt::Chart::Axis::Y).setLocation(Wt::Chart::AxisValue::Zero);

        chart_->setPlotAreaPadding(120, Wt::Side::Right);
        chart_->setPlotAreaPadding(40, Wt::Side::Top | Wt::Side::Bottom);
        
        auto s = std::make_unique<Wt::Chart::WDataSeries>(1, Wt::Chart::SeriesType::Curve);
        s->setShadow(Wt::WShadow(3, 3, Wt::WColor(0, 0, 0, 127), 3));
        chart_->addSeries(std::move(s));

        // Установка стилей
        chart_->resize(800, 300);
        chart_->setMargin(10, Wt::Side::Top | Wt::Side::Bottom);            
        chart_->setMargin(Wt::WLength::Auto, Wt::Side::Left | Wt::Side::Right);
    }

    std::shared_ptr<Wt::WStandardItemModel> model_;
    Wt::Chart::WCartesianChart* chart_;
    Wt::WLineEdit* inputField_;
};


int main(int argc, char** argv) {
    try {
        Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

        // Добавление точки входа для вашего приложения
        server.addEntryPoint(Wt::EntryPointType::Application, [](const Wt::WEnvironment& env) {
            return std::make_unique<MyApplication>(env);
            });

        // Запуск сервера на локальном адресе и порту
        if (server.start()) {
            std::cout << "server is operating on http://localhost:8080/hello" << std::endl;
            int sig = Wt::WServer::waitForShutdown();
            server.stop();
            return sig;
        }
        else {
            return 1;
        }
    }
    catch (Wt::WServer::Exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
        return 1;
    }
}

/*
#include <Wt/WApplication.h>
#include <Wt/WServer.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

class MyApplication : public Wt::WApplication {
public:
    MyApplication(const Wt::WEnvironment& env)
        : Wt::WApplication(env) {
        setTitle("www.jopa");


        Wt::WContainerWidget* container = root();

        // Добавляем текстовый виджет на страницу
        container->addWidget(std::make_unique<Wt::WText>("Hello world, this is a text on the page itself"));
    }
};

    void handleInput() {
        std::string inputText = inputField_->text().toUTF8();

        try {
            float intValue = std::stof(inputText);
            resultLabel_->setText("pow(YourValue,2) is:  " + std::to_string(pow(intValue,2)));
        }
        catch (std::invalid_argument&) {
            resultLabel_->setText("Error: Incorrect form ");
        }
        catch (std::out_of_range&) {
            resultLabel_->setText("Error: The value is too big, or too low ");
        }
    }

            // Добавляем кнопку для отправки данных
        Wt::WPushButton* button1 = container->addWidget(std::make_unique<Wt::WPushButton>("Send"));
        button1->clicked().connect(this, &MyApplication::handleInput);


                // Добавляем метку для вывода результата
        resultLabel_ = container->addWidget(std::make_unique<Wt::WText>(""));


                // Добавляем отступ для красоты
        container->addWidget(std::make_unique<Wt::WBreak>());
*/