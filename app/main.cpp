
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QStackedWidget>

QWidget* createPage(const QString& title, const QString& description)
{
    QWidget* page = new QWidget();

    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->setContentsMargins(35, 30, 35, 30);
    layout->setSpacing(15);

    QLabel* heading = new QLabel(title);
    heading->setObjectName("pageTitle");

    QLabel* subtitle = new QLabel(description);
    subtitle->setObjectName("pageSubtitle");

    layout->addWidget(heading);
    layout->addWidget(subtitle);
    layout->addStretch();

    return page;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("FileSuite");
    window.resize(1100, 700);

    QWidget* central = new QWidget();
    QHBoxLayout* mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Sidebar
    QListWidget* sidebar = new QListWidget();
    sidebar->setFixedWidth(220);

    sidebar->addItems({
        "Overview",
        "File Organizer",
        "Storage Analyzer",
        "Duplicate Finder",
        "Bulk Renamer"
    });

    // Content area
    QStackedWidget* pages = new QStackedWidget();

    pages->addWidget(
        createPage("Welcome to FileSuite",
                   "Manage your files intelligently.")
    );

    pages->addWidget(
        createPage("File Organizer",
                   "Automatically organize files into categories.")
    );

    pages->addWidget(
        createPage("Storage Analyzer",
                   "Understand how your storage is being used.")
    );

    pages->addWidget(
        createPage("Duplicate Finder",
                   "Find duplicate files and reclaim storage.")
    );

    pages->addWidget(
        createPage("Bulk Renamer",
                   "Rename multiple files with custom rules.")
    );

    // Navigation
    QObject::connect(
        sidebar,
        &QListWidget::currentRowChanged,
        pages,
        &QStackedWidget::setCurrentIndex
    );

    sidebar->setCurrentRow(0);

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(pages, 1);

    window.setCentralWidget(central);

    // Dark theme
    window.setStyleSheet(R"(
        QMainWindow, QWidget {
            background-color: #151922;
            color: #E5E7EB;
            font-family: "Segoe UI";
        }

        QListWidget {
            background-color: #1D2330;
            border: none;
            padding: 12px;
            outline: none;
        }

        QListWidget::item {
            padding: 14px;
            margin: 3px;
            border-radius: 7px;
        }

        QListWidget::item:selected {
            background-color: #334B70;
            color: white;
        }

        QListWidget::item:hover {
            background-color: #293447;
        }

        QLabel#pageTitle {
            font-size: 28px;
            font-weight: bold;
            color: #FFFFFF;
        }

        QLabel#pageSubtitle {
            font-size: 14px;
            color: #9CA3AF;
        }
    )");

    window.show();

    return app.exec();
}
