#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->textures = new std::vector<QString>();
    this->tiles = new std::vector<Tile*>();
    this->tc_win = new TileCreator();
    connect(this->tc_win,SIGNAL(on_new_tile(Tile*)),this,SLOT(on_new_tile(Tile*))); // Connecte l'evenement on_new_tile de la fenetre de création de tile a celui du mainwindow (permet l'echange de tile entre les deux fenetres)
    // TEMP !!!!
    this->textures->push_back("/home/johnsudaar/Documents/Hellen/Hellen/res/PackMario/sprites/tileset.gif");
    this->textures->push_back("/home/johnsudaar/Documents/Hellen/Hellen/res/TestPack/sprites/tileset.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_cr_tile_clicked() // Ouverture et initialisation de la fenetre des tiles
{
    this->tc_win->importTextures(this->textures);
    this->tc_win->setModal(true); // La fenetre de tiles prend la main (impossible d'acceder aux autres fenètres de l'application)
    this->tc_win->show();
}

void MainWindow::on_bgn_imp_text_clicked() // Ouverture de la fenetre d'ajout de texture (puis ajout de la texture choisie en mémoire)
{
    QString str = QFileDialog::getOpenFileName(this,"Open Image");
    this->textures->push_back(str);
}

void MainWindow::on_new_tile(Tile *tile){
    this->tiles->push_back(tile);
    this->updateItems();
}

void MainWindow::updateItems(){
    this->ui->lv_tiles->clear();
    for(std::vector<Tile*>::iterator it = this->tiles->begin(); it != this->tiles->end(); ++it){
        QListWidgetItem* item = new QListWidgetItem();
        QVariant variant = QVariant::fromValue((*it)->getName());
        item->setIcon((*it)->getPixmap());
        item->setData(Qt::UserRole, variant);
        this->ui->lv_tiles->addItem(item);
    }
}

Tile* MainWindow::getTile(QString name){
    for(std::vector<Tile*>::iterator it = this->tiles->begin(); it != this->tiles->end(); ++it){
        if(name.compare((*it)->getName()) == 0){
            return *it;
        }
    }
    return 0;
}

bool MainWindow::deleteTile(QString name){
    for(std::vector<Tile*>::iterator it = this->tiles->begin(); it != this->tiles->end(); ++it){
        if(name.compare((*it)->getName()) == 0){
            this->tiles->erase(it);
            return true;
        }
    }
    return false;
}

void MainWindow::on_pb_delete_tiles_clicked()
{
    if(this->ui->lv_tiles->currentIndex().isValid()){
        QVariant var = this->ui->lv_tiles->currentItem()->data(Qt::UserRole);
        QString name = var.value<QString>();
        if(! this->deleteTile(name)){
            QMessageBox msgBox;
            msgBox.setText("Opération impossible.");
            msgBox.exec();
        }
        this->updateItems();
    }else{
        QMessageBox msgBox;
        msgBox.setText("Aucune tile séléctionné.");
        msgBox.exec();
    }

}

void MainWindow::on_pb_button_test_clicked()
{
    qDebug()<<"Test";
}
