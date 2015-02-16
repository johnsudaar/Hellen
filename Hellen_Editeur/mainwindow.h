#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QDebug>
#include <QVariant>
#include <QMessageBox>

#include "tilecreator.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_cr_tile_clicked();
    void on_bgn_imp_text_clicked();
    void on_new_tile(Tile* tile);
    void on_pb_delete_tiles_clicked();

    void on_pb_button_test_clicked();

private:
    Tile* getTile(QString name);
    bool deleteTile(QString name);

    void updateItems();
    TileCreator* tc_win;
    std::vector<QString>* textures;
    std::vector<Tile*>* tiles;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
