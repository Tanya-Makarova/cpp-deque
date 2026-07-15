#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algo.h"

#include <algorithm>
#include <random>
#include <deque>
#include <iterator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    std::random_device rd;
    random_gen_ = std::mt19937(rd());

    connect(ui->btn_push_back, &QPushButton::clicked, this, &MainWindow::OnPushBack);
    connect(ui->btn_pop_back, &QPushButton::clicked, this, &MainWindow::OnPopBack);
    connect(ui->btn_tea, &QPushButton::clicked, this, &MainWindow::OnTea);
    connect(ui->btn_cakes, &QPushButton::clicked, this, &MainWindow::OnCakes);
    connect(ui->btn_edit, &QPushButton::clicked, this, &MainWindow::OnEdit);
    connect(ui->btn_erase, &QPushButton::clicked, this, &MainWindow::OnErase);
    connect(ui->btn_insert, &QPushButton::clicked, this, &MainWindow::OnInsert);
    connect(ui->btn_inc, &QPushButton::clicked, this, &MainWindow::OnInc);
    connect(ui->btn_dec, &QPushButton::clicked, this, &MainWindow::OnDec);
    connect(ui->btn_begin, &QPushButton::clicked, this, &MainWindow::OnBegin);
    connect(ui->btn_end, &QPushButton::clicked, this, &MainWindow::OnEnd);

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetRandomGen(const std::mt19937& gen)
{
    random_gen_ = gen;
}

void MainWindow::ApplyIterator() {
    const auto offset = std::distance(deque_model_.items.begin(), deque_model_.iterator);

    ui->list_widget->blockSignals(true);
    ui->list_widget->setCurrentRow(static_cast<int>(offset));
    ui->list_widget->blockSignals(false);

    const bool at_end = deque_model_.iterator == deque_model_.items.end();
    ui->btn_edit->setEnabled(!at_end);
    ui->btn_erase->setEnabled(!at_end);
    ui->btn_inc->setEnabled(!at_end);
    ui->btn_dec->setEnabled(deque_model_.iterator != deque_model_.items.begin());

    if (at_end) {
        ui->txt_elem_content->clear();
    } else {
        ui->txt_elem_content->setText(QString::fromStdString(*deque_model_.iterator));
    }
}

void MainWindow::ApplyModel() {
    auto preserve_iter = deque_model_.iterator;

    ui->list_widget->clear();

    QStringList list;
    for (size_t i = 0; i < deque_model_.items.size(); ++i) {
        list.push_back(QString("%1: %2")
                           .arg(i)
                           .arg(QString::fromStdString(deque_model_.items[i])));
    }
    list.push_back("end");
    ui->list_widget->addItems(list);

    deque_model_.iterator = preserve_iter;

    ui->txt_size->setText(QString::number(deque_model_.items.size()));
    ui->btn_pop_back->setEnabled(!deque_model_.items.empty());
    ui->btn_pop_front->setEnabled(!deque_model_.items.empty());

    ApplyIterator();
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    if (currentRow < 0) {
        return;
    }
    deque_model_.iterator = deque_model_.items.begin() + currentRow;
    ApplyIterator();
}

void MainWindow::OnPushBack() {
    deque_model_.items.push_back(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::OnPopBack() {
    if (!deque_model_.items.empty()) {
        deque_model_.items.pop_back();
    }
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_clear_clicked() {
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_resize_clicked() {
    size_t size = ui->txt_size->text().toUInt();
    size = std::min(size, size_t{1000});
    deque_model_.items.resize(size);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_find_clicked() {
    const auto value = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator = std::find(deque_model_.items.begin(), deque_model_.items.end(), value);
    ApplyIterator();
}

void MainWindow::on_btn_count_clicked() {
    const auto value = ui->le_count->text().toStdString();
    const auto count = std::count(deque_model_.items.begin(), deque_model_.items.end(), value);
    ui->lbl_count->setText(QString::number(count));
}

void MainWindow::on_btn_min_element_clicked() {
    deque_model_.iterator = std::min_element(deque_model_.items.begin(), deque_model_.items.end());
    ApplyIterator();
}

void MainWindow::on_btn_max_element_clicked() {
    deque_model_.iterator = std::max_element(deque_model_.items.begin(), deque_model_.items.end());
    ApplyIterator();
}

void MainWindow::OnTea() {
    deque_model_.items = {
        "Чай Лунцзин",
        "Эрл Грей",
        "Сенча",
        "Пуэр",
        "Дарджилинг",
        "Ассам",
        "Матча",
        "Ганпаудер",
        "Оолонг",
        "Лапсанг Сушонг"
    };
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::OnCakes() {
    deque_model_.items = {
        "Красный бархат",
        "Наполеон",
        "Медовик",
        "Тирамису",
        "Прага",
        "Чизкейк",
        "Захер",
        "Эстерхази",
        "Морковный торт",
        "Чёрный лес",
    };
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::OnEdit() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        *deque_model_.iterator = ui->txt_elem_content->text().toStdString();
        ApplyModel();
    }
}

void MainWindow::OnErase() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        deque_model_.items.erase(deque_model_.iterator);
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}

void MainWindow::OnInsert() {
    deque_model_.items.insert(deque_model_.iterator, ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::OnInc() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        ++deque_model_.iterator;
        ApplyIterator();
    }
}

void MainWindow::OnDec() {
    if (deque_model_.iterator != deque_model_.items.begin()) {
        --deque_model_.iterator;
        ApplyIterator();
    }
}

void MainWindow::OnBegin() {
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::OnEnd() {
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
}

void MainWindow::on_merge_sort_btn_clicked()
{
    const auto comparator = [](const std::string& a, const std::string& b) { return a < b; };
    deque_model_.items = MergeSort(deque_model_.items, comparator);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_merge_sort_without_reg_btn_clicked()
{
    const auto comparator = [](const std::string& a, const std::string& b){
                  std::string sa = a;
                  std::string sb = b;

                  std::transform(sa.begin(), sa.end(), sa.begin(),
                                 [](unsigned char c) { return std::tolower(c); });
                  std::transform(sb.begin(), sb.end(), sb.begin(),
                                 [](unsigned char c) { return std::tolower(c); });

                  return sa < sb;
              };
    deque_model_.items = MergeSort(deque_model_.items, comparator);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_unique_btn_clicked()
{
    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        return;
    }

    deque_model_.items.erase(
        std::unique(deque_model_.items.begin(), deque_model_.items.end()),
        deque_model_.items.end()
        );

    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_shuffle_btn_clicked()
{
    std::shuffle(deque_model_.items.begin(), deque_model_.items.end(), random_gen_);
    ApplyModel();
}


void MainWindow::on_reverse_btn_clicked()
{
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());
    ApplyModel();
}


void MainWindow::on_btn_push_front_clicked()
{
    deque_model_.items.push_front(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_pop_front_clicked()
{
    if (!deque_model_.items.empty()) {
        deque_model_.items.pop_front();
    }
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_upper_bound_btn_clicked()
{
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        deque_model_.iterator = std::upper_bound(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toStdString());
        ApplyIterator();
    }
}


void MainWindow::on_lower_bound_btn_clicked()
{
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        deque_model_.iterator = std::lower_bound(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toStdString());
        ApplyIterator();
    }
}

