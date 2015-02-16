#ifndef TILECREATOR_H
#define TILECREATOR_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDebug>

#include "tile.h"

namespace Ui {
class TileCreator;
}

class TileCreator : public QDialog
{
    Q_OBJECT

public:
    void importTextures(std::vector<QString>* str);
    explicit TileCreator(QWidget *parent = 0);
    Tile* getTile();
    ~TileCreator();

signals:
    void on_new_tile(Tile* tile);
private slots:
    void on_pb_cancel_clicked();
    void on_pb_ok_clicked();
    void on_valueChanged(int val);
    void on_cb_texture_currentIndexChanged(const QString &arg1);
private:
    void initInputs();
    void updateInputs();
    void updatePic();
    QPixmap cur_pix;
    QGraphicsScene* scene;
    Ui::TileCreator *ui;
    bool pic_loaded;
};

#endif // TILECREATOR_H
