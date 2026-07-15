#pragma once

#include <QMainWindow>
#include <random>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetRandomGen(const std::mt19937& gen);

private slots:
    void OnPushBack();
    void OnPopBack();
    void OnTea();
    void OnCakes();
    void OnEdit();
    void OnErase();
    void OnInsert();
    void OnInc();
    void OnDec();
    void OnBegin();
    void OnEnd();
    void on_list_widget_currentRowChanged(int currentRow);
    void on_btn_clear_clicked();
    void on_btn_resize_clicked();
    void on_btn_find_clicked();
    void on_btn_count_clicked();
    void on_btn_min_element_clicked();
    void on_btn_max_element_clicked();
    void on_merge_sort_btn_clicked();
    void on_merge_sort_without_reg_btn_clicked();
    void on_unique_btn_clicked();
    void on_shuffle_btn_clicked();
    void on_reverse_btn_clicked();
    void on_btn_push_front_clicked();
    void on_btn_pop_front_clicked();
    void on_upper_bound_btn_clicked();

    void on_lower_bound_btn_clicked();

private:
    void ApplyModel();
    void ApplyIterator();

private:
    Model deque_model_;
    Ui::MainWindow *ui;
    std::mt19937 random_gen_;
};
