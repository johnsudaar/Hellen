#include "tilecreator.h"
#include "ui_tilecreator.h"

TileCreator::TileCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TileCreator)
{
    ui->setupUi(this);
    this->scene = new QGraphicsScene();
    ui->graphicsView->setScene(this->scene);
    this->pic_loaded = false;
    connect(this->ui->sb_h,SIGNAL(valueChanged(int)),this,SLOT(on_valueChanged(int))); // Detecte le changement de valeur des combobox x,y,w,h
    connect(this->ui->sb_w,SIGNAL(valueChanged(int)),this,SLOT(on_valueChanged(int)));
    connect(this->ui->sb_x,SIGNAL(valueChanged(int)),this,SLOT(on_valueChanged(int)));
    connect(this->ui->sb_y,SIGNAL(valueChanged(int)),this,SLOT(on_valueChanged(int)));
}

TileCreator::~TileCreator()
{
    delete ui;
}

void TileCreator::importTextures(std::vector<QString>* str){ // Remplis la combobox (et définit la première image comme l'image courante)
    bool first = true;
    this->pic_loaded = false;
    this->scene->clear();
    for(std::vector<QString>::iterator it = str->begin(); it != str->end(); ++it){ // On parcours le vecteur passé en parametre
        if(first){
            this->cur_pix = QPixmap::fromImage(QImage(*it)); // Si c'est la premlière chaine on la définit comme image courante
            this->initInputs();
            this->updatePic();
            this->pic_loaded = true;
            first = false;
        }
        this->ui->cb_texture->addItem(*it);
    }
}

void TileCreator::initInputs(){ // Reinitialisation des combobox x,y,w,h
    this->ui->sb_x->setMaximum(this->cur_pix.width());
    this->ui->sb_y->setMaximum(this->cur_pix.height());
    this->ui->sb_x->setValue(0);
    this->ui->sb_y->setValue(0);
    this->ui->sb_w->setMaximum(this->cur_pix.width());
    this->ui->sb_h->setMaximum(this->cur_pix.height());
    this->ui->sb_w->setValue(this->cur_pix.width());
    this->ui->sb_h->setValue(this->cur_pix.height());
    this->ui->le_name->setText("");
}

void TileCreator::updateInputs(){ // Mise a jour des maximum pour w et h en fonction de x et y
    this->ui->sb_h->setMaximum(this->cur_pix.height() - this->ui->sb_y->value());
    this->ui->sb_w->setMaximum(this->cur_pix.width()  - this->ui->sb_x->value());
}

void TileCreator::updatePic(){ // Appelé lors de la modification des paramètres x,y,w ou h : Crop l'image en fonction de ces paramètres
    scene->clear();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(cur_pix.copy(this->ui->sb_x->value(),this->ui->sb_y->value(),this->ui->sb_w->value(),this->ui->sb_h->value()));
    scene->addItem(item);
    scene->setSceneRect(0,0,this->cur_pix.width(),this->cur_pix.height());
}

void TileCreator::on_pb_cancel_clicked() // Appelé lors de l'annulation
{
    this->initInputs();
    this->updatePic();
    this->close();
}

void TileCreator::on_pb_ok_clicked() // Appelé lors de la validation
{
    emit on_new_tile(this->getTile());
    this->ui->le_name->setText("");
    this->close();
}

void TileCreator::on_valueChanged(int val) // Appelé lors du changement de valeur de x,y,w ou h
{
    this->updateInputs();
    this->updatePic();
}

Tile* TileCreator::getTile(){ // Retourne un  objet de type Tile en fonction de la configuration courante
    Tile* tile = new Tile(this->ui->sb_x->value(),this->ui->sb_y->value(),this->ui->sb_w->value(), this->ui->sb_h->value(),this->ui->cb_texture->currentText(),"");
    return tile;
}

void TileCreator::on_cb_texture_currentIndexChanged(const QString &arg1) // Quand on change de choix dans la combobx
{
    this->cur_pix = QPixmap::fromImage(QImage(this->ui->cb_texture->currentText()));
    this->initInputs();
    this->updatePic();
    this->pic_loaded = true;
}
