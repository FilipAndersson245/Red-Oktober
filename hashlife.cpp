#include "hashlife.h"
#include "ui_hashlife.h"
// demo restricts level loading to 10x10 grid size //
#define ROOTDIR ":/levels/"
// how many levels of each grid and difficulty do we have //
#define IPTESTURL "http://api.ipify.org"
Hashlife::Hashlife(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hashlife)
{
    ui->setupUi(this);
    _mainScene = new QGraphicsScene();
    _mainScene->setSceneRect(QRectF(0, 0, WINDOWSIZE, WINDOWSIZE));
    _levelFromWeb = "";
    ui->_graphicsView->setScene(_mainScene);
    ui->_graphicsView->show();
    ui->_graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    ui->menuBar->hide();
    checkInternetConnection();
    checkWebLoadingEngine();
    addMenuGraphics();
    autoScaleView();
}

void Hashlife::addMenuGraphics()
{
    //_backgroundImage = new QGraphicsPixmapItem(QPixmap(":/images/background_image.png"));
    //_mainScene->addItem(_backgroundImage);
    //ui->_graphicsView->fitInView(_backgroundImage, Qt::KeepAspectRatio);
    //_mainScene->setBackgroundBrush(_backgroundImage);

    _btnNewGame = new QPushButton;
    _btnNewGame->setGeometry(QRect(120, 30, 360, 150));
    _btnNewGame->setText("New Game");
    _btnNewGame->setFont(QFont("Gill Sans MT", 18, QFont::Bold, true));
    _proxyNewGame = new QGraphicsProxyWidget;
    _proxyNewGame = _mainScene->addWidget(_btnNewGame);
    connect(_btnNewGame, SIGNAL(released()), this, SLOT(setupGame()));
    _btnHelp = new QPushButton;
    _btnHelp->setGeometry(QRect(120, 225, 360, 150));
    _btnHelp->setText("Help");
    _btnHelp->setFont(QFont("Gill Sans MT", 18, QFont::Bold, true));
    _proxyHelp = new QGraphicsProxyWidget;
    _proxyHelp = _mainScene->addWidget(_btnHelp);
    connect(_btnHelp, SIGNAL(released()), this, SLOT(help()));
    _btnExit = new QPushButton;
    _btnExit->setGeometry(QRect(120, 420, 360, 150));
    _btnExit->setText("Exit");
    _btnExit->setFont(QFont("Gill Sans MT", 18, QFont::Bold, true));
    _proxyExit = new QGraphicsProxyWidget;
    _proxyExit = _mainScene->addWidget(_btnExit);
    connect(_btnExit, SIGNAL(released()), this, SLOT(exit()));
}

void Hashlife::newGame()
{
    _logic = new GameLogic(_gridSizeSelection, _mainScene);
    connect(_logic, SIGNAL(endGameButtonClickedSignal()), this, SLOT(on_actionEnd_Game_triggered()));
    _mainScene->removeItem(_btnGrid10->graphicsProxyWidget());
    _mainScene->removeItem(_btnGrid15->graphicsProxyWidget());
    _mainScene->removeItem(_btnGrid20->graphicsProxyWidget());
    _mainScene->removeItem(_btnEasy->graphicsProxyWidget());
    _mainScene->removeItem(_btnMedium->graphicsProxyWidget());
    _mainScene->removeItem(_btnHard->graphicsProxyWidget());
    _mainScene->removeItem(_btnStart->graphicsProxyWidget());
    _mainScene->removeItem(_btnReturn->graphicsProxyWidget());
    _mainScene->removeItem(_difficultyLabel->graphicsProxyWidget());
    _mainScene->removeItem(_gridLabel->graphicsProxyWidget());
    _mainScene->removeItem(_boardLabel->graphicsProxyWidget());
    _mainScene->removeItem(_comboGridLabel->graphicsProxyWidget());
    _mainScene->removeItem(_comboDifficultyLabel->graphicsProxyWidget());
    _mainScene->removeItem(_boardSelector->graphicsProxyWidget());
    ui->menuBar->show();
    ui->_graphicsView->fitInView( _mainScene->sceneRect(), Qt::KeepAspectRatio);
    qDebug() << "new game";
    try
    {
        chosenMap();

    }catch(QString ERRORCODE)
    {QErrorMessage fileProblem(this); fileProblem.showMessage(ERRORCODE); fileProblem.exec();}
    setupGameGraphics();
}

void Hashlife::help()
{
    qDebug() << "seek help";
    const int width = 520;
    const int height = 800;
    const int marginLeft = 10;
    const int marginRight = 20;
    QDialog* helpDialog = new QDialog();
    helpDialog->setFixedSize(QSize(width,height));
    helpDialog->setStyleSheet("background-color:#ffffff;");

    /*QLabel gifExplain(helpDialog);
    QMovie *pictureGif = new QMovie(":/images/tutorial.mp4");
    gifExplain.setMovie(pictureGif);
    pictureGif->setScaledSize(QSize(width-marginRight,width-marginRight));
    pictureGif->start();
    gifExplain.setGeometry(marginLeft,0,width-marginRight,width-marginRight);*/

    QMediaPlayer * player = new QMediaPlayer;
    QVideoWidget * videoWidget = new QVideoWidget(helpDialog);
    QMediaContent myVideo(QUrl("qrc:/images/tutorial.avi"));
    player->setMedia(myVideo);
    player->setVideoOutput(videoWidget);
    videoWidget->show();
    videoWidget->setGeometry(marginLeft,0,width-marginRight,width-marginRight);

    player->play();

    QLabel ruleLabel("Rules:\n"
                     "- The goal of the game is to connect nodes together via bridges.\n"
                     "- The game ends when all nodes have as many bridges going out from \n"
                     "     them as their own value.\n"
                     "- All nodes must form one single connection.\n"
                     "- Each node may contain 0, 1 or 2 bridges in any given direction.\n"
                     "- You place a bridge by hovering over a node and selecting\n"
                     "     a valid bridge by left clicking with the mouse.\n"
                     "- You can remove a bridge by right clicking on it.\n"
                     "- Bridges may not cross each other.\n"
                     "- Bridges can only be vertical or horizontal.",
                     helpDialog);
    ruleLabel.setFont(QFont("Gill Sans MT", 11, QFont::Bold, false));
    ruleLabel.setGeometry(marginLeft,width+10,width-marginRight,height-width);
    helpDialog->exec();
}

void Hashlife::exit()
{
    qApp->exit();
}

void Hashlife::returnToMenu()
{
    qDebug() << "Return";
    _mainScene->removeItem(_btnGrid10->graphicsProxyWidget());
    _mainScene->removeItem(_btnGrid15->graphicsProxyWidget());
    _mainScene->removeItem(_btnGrid20->graphicsProxyWidget());
    _mainScene->removeItem(_btnEasy->graphicsProxyWidget());
    _mainScene->removeItem(_btnMedium->graphicsProxyWidget());
    _mainScene->removeItem(_btnHard->graphicsProxyWidget());
    _mainScene->removeItem(_btnStart->graphicsProxyWidget());
    _mainScene->removeItem(_btnReturn->graphicsProxyWidget());
    _mainScene->removeItem(_difficultyLabel->graphicsProxyWidget());
    _mainScene->removeItem(_gridLabel->graphicsProxyWidget());
    _mainScene->removeItem(_boardLabel->graphicsProxyWidget());
    _mainScene->removeItem(_comboGridLabel->graphicsProxyWidget());
    _mainScene->removeItem(_comboDifficultyLabel->graphicsProxyWidget());
    _mainScene->removeItem(_boardSelector->graphicsProxyWidget());
    addMenuGraphics();
}

void Hashlife::difficultyClicked()
{
    qDebug() << "Difficulty button was clicked";
    _boardSelector->setCurrentIndex(0);
    switch(_grpDifficulty->checkedId())
    {
    case 0:
        _comboDifficultyLabel->setText("Easy:");
        break;
    case 1:
        _comboDifficultyLabel->setText("Medium:");;
        break;
    case 2:
        _comboDifficultyLabel->setText("Hard:");;
        break;
    default:
        break;
    }
}

void Hashlife::gridClicked()
{
    qDebug() << "Grid button was clicked" << _grpGridSize->checkedId();
    _boardSelector->setCurrentIndex(0);
    switch(_grpGridSize->checkedId())
    {
    case 0:
        _gridSizeSelection = 9;
        _comboGridLabel->setText("9 x 9:");
        break;
    case 1:
        _gridSizeSelection = 13;
        _comboGridLabel->setText("13 x 13:");;
        break;
    case 2:
        _gridSizeSelection = 17;
        _comboGridLabel->setText("17 x 17:");;
        break;
    default:
        break;
    }
}

void Hashlife::setupGameGraphics()
{
    _logic->addGameGraphics(_mainScene);
}

void Hashlife::resizeEvent(QResizeEvent *event)
{
    autoScaleView();
}

void Hashlife::showEvent(QShowEvent *event)
{
    ui->_graphicsView->fitInView( _mainScene->sceneRect(), Qt::KeepAspectRatio);
}

void Hashlife::autoScaleView()
{
    ui->_graphicsView->fitInView( _mainScene->sceneRect(), Qt::KeepAspectRatio);

    //_backgroundImage->setPos(ui->_graphicsView->mapToScene(QPoint(0,0)));
}

Hashlife::~Hashlife()
{

}


void Hashlife::setupGame()
{
    _mainScene->removeItem(_btnNewGame->graphicsProxyWidget());
    _mainScene->removeItem(_btnHelp->graphicsProxyWidget());
    _mainScene->removeItem(_btnExit->graphicsProxyWidget());
    _gridSizeSelection = 9;
    qDebug() << "Tried to create game";
    _btnReturn = new QPushButton;
    _btnReturn->setGeometry(QRect(480, 0, 120, 45));
    _btnReturn->setText("Return");
    _btnReturn->setFont(QFont("Gill Sans MT", 18, QFont::Bold, true));;
    _btnReturn->setMaximumSize(120, 45);
    _proxyReturn = new QGraphicsProxyWidget;
    _proxyReturn = _mainScene->addWidget(_btnReturn);
    connect(_btnReturn, SIGNAL(clicked()), this, SLOT(returnToMenu()));
    _gridLabel = new QLabel;
    _gridLabel->setText("Select Grid Size:");
    _gridLabel->setFont(QFont("Gill Sans MT", 12, QFont::Bold, false));
    _gridLabel->setGeometry(QRect(237, 30, 150, 30));
    _gridLabel->setStyleSheet("background-color: rgba(0,0,0,0%)");
    _proxyGridLabel = new QGraphicsProxyWidget;
    _proxyGridLabel = _mainScene->addWidget(_gridLabel);
    _btnGrid10 = new QPushButton;
    _btnGrid10->setGeometry(QRect(90, 60, 120, 120));
    _btnGrid10->setText("9 x 9");
    _btnGrid10->setFont(QFont("Gill Sans MT", 18, QFont::Bold, true));
    _btnGrid10->setCheckable(true);
    _btnGrid10->setChecked(true);
    _btnGrid10->setMaximumSize(120, 120);
    _proxyGrid10 = new QGraphicsProxyWidget;
    _proxyGrid10 = _mainScene->addWidget(_btnGrid10);
    _btnGrid15 = new QPushButton;
    _btnGrid15->setGeometry(QRect(240, 60, 120, 120));
    _btnGrid15->setText("13 x 13");
    _btnGrid15->setFont(QFont("Gill Sans MT", 18, QFont::Bold, true));
    _btnGrid15->setCheckable(true);
    _btnGrid15->setMaximumSize(120, 120);
    _proxyGrid15 = new QGraphicsProxyWidget;
    _proxyGrid15 = _mainScene->addWidget(_btnGrid15);
    _btnGrid20 = new QPushButton;
    _btnGrid20->setGeometry(QRect(390, 60, 120, 120));
    _btnGrid20->setText("17 x 17");
    _btnGrid20->setFont(QFont("Gill Sans MT", 18, QFont::Bold, true));
    _btnGrid20->setCheckable(true);
    _btnGrid20->setMaximumSize(120, 120);
    _proxyGrid20 = new QGraphicsProxyWidget;
    _proxyGrid20 = _mainScene->addWidget(_btnGrid20);
    _difficultyLabel = new QLabel;
    _difficultyLabel->setText("Select Difficulty:");
    _difficultyLabel->setFont(QFont("Gill Sans MT", 12, QFont::Bold, false));
    _difficultyLabel->setGeometry(QRect(234, 180, 150, 30));
    _difficultyLabel->setStyleSheet("background-color: rgba(0,0,0,0%)");
    _proxyDifficultyLabel = new QGraphicsProxyWidget;
    _proxyDifficultyLabel = _mainScene->addWidget(_difficultyLabel);
    _btnEasy = new QPushButton;
    _btnEasy->setGeometry(QRect(90, 210, 120, 120));
    _btnEasy->setText("Easy");
    _btnEasy->setFont(QFont("Gill Sans MT", 18, QFont::Bold, true));
    _btnEasy->setCheckable(true);
    _btnEasy->setChecked(true);
    _btnEasy->setMaximumSize(120, 120);
    _proxyEasy = new QGraphicsProxyWidget;
    _proxyEasy = _mainScene->addWidget(_btnEasy);
    _btnMedium = new QPushButton;
    _btnMedium->setGeometry(QRect(240, 210, 120, 120));
    _btnMedium->setText("Medium");
    _btnMedium->setFont(QFont("Gill Sans MT", 18, QFont::Bold, true));
    _btnMedium->setCheckable(true);
    _btnMedium->setMaximumSize(120, 120);
    _proxyMedium = new QGraphicsProxyWidget;
    _proxyMedium = _mainScene->addWidget(_btnMedium);
    _btnHard = new QPushButton;
    _btnHard->setGeometry(QRect(390, 210, 120, 120));
    _btnHard->setText("Hard");
    _btnHard->setFont(QFont("Gill Sans MT", 18, QFont::Bold, true));
    _btnHard->setCheckable(true);
    _btnHard->setMaximumSize(120, 120);
    _proxyHard = new QGraphicsProxyWidget;
    _proxyHard = _mainScene->addWidget(_btnHard);
    _btnStart = new QPushButton;
    _btnStart->setGeometry(QRect(120, 420, 360, 150));
    _btnStart->setText("Start Game");
    _btnStart->setFont(QFont("Gill Sans MT", 18, QFont::Bold, true));;
    _proxyStart = new QGraphicsProxyWidget;
    _proxyStart = _mainScene->addWidget(_btnStart);
    connect(_btnStart, SIGNAL(clicked()), this, SLOT(newGame()));
    _boardLabel = new QLabel;
    _boardLabel->setText("Select Game Board:");
    _boardLabel->setFont(QFont("Gill Sans MT", 12, QFont::Bold, false));
    _boardLabel->setGeometry(QRect(228, 330, 160, 30));
    _boardLabel->setStyleSheet("background-color: rgba(0,0,0,0%)");
    _proxyBoardLabel = new QGraphicsProxyWidget;
    _proxyBoardLabel = _mainScene->addWidget(_boardLabel);
    _comboDifficultyLabel = new QLabel;
    _comboDifficultyLabel->setText("Easy:");
    _comboDifficultyLabel->setFont(QFont("Gill Sans MT", 11, QFont::Bold, false));
    _comboDifficultyLabel->setGeometry(QRect(156, 363, 90, 30));
    _comboDifficultyLabel->setStyleSheet("background-color: rgba(0,0,0,0%)");
    _proxyComboDifficultyLabel = new QGraphicsProxyWidget;
    _proxyComboDifficultyLabel = _mainScene->addWidget(_comboDifficultyLabel);
    _comboGridLabel = new QLabel;
    _comboGridLabel->setText("9 x 9:");
    _comboGridLabel->setFont(QFont("Gill Sans MT", 11, QFont::Bold, false));
    _comboGridLabel->setGeometry(QRect(90, 363, 90, 30));
    _comboGridLabel->setStyleSheet("background-color: rgba(0,0,0,0%)");
    _proxyComboGridLabel = new QGraphicsProxyWidget;
    _proxyComboGridLabel = _mainScene->addWidget(_comboGridLabel);
    _grpGridSize = new QButtonGroup;
    _grpGridSize->addButton(_btnGrid10, 0);
    _grpGridSize->addButton(_btnGrid15, 1);
    _grpGridSize->addButton(_btnGrid20, 2);
    connect(_grpGridSize, SIGNAL(buttonClicked(int)), this, SLOT(gridClicked()));
    _grpDifficulty = new QButtonGroup;
    _grpDifficulty->addButton(_btnEasy, 0);
    _grpDifficulty->addButton(_btnMedium, 1);
    _grpDifficulty->addButton(_btnHard, 2);
    connect(_grpDifficulty, SIGNAL(buttonClicked(int)), this, SLOT(difficultyClicked()));
    _boardSelector = new QComboBox;
    _boardSelector->setGeometry(QRect(225, 360, 285, 36));
    _boardSelector->setFont(QFont("Gill Sans MT", 12, QFont::Bold, false));
    _boardSelector->setMaximumSize(285, 36);
    if (!_levelFromWeb.isEmpty())
    {
        _boardSelector->insertItem(0, "Random Online");
    }

    _boardSelector->insertItem(1, "Level 1");
    _boardSelector->insertItem(2, "Level 2");
    _boardSelector->insertItem(3, "Level 3");
    _boardSelector->insertItem(4, "Level 4");
    _boardSelector->insertItem(5, "Level 5");
    _boardSelector->insertItem(6, "Level 6");
    _boardSelector->insertItem(7, "Level 7");
    _proxyBoardSelector = new QGraphicsProxyWidget;
    _proxyBoardSelector = _mainScene->addWidget(_boardSelector);
}

void Hashlife::on_actionEnd_Game_triggered()
{
    _mainScene->clear();
    _logic->endGame();
    addMenuGraphics();
}

void Hashlife::on_actionHelp_triggered()
{
    help();
}

//Creates a string to the location of the target file based on player choices
void Hashlife::chosenMap()
{
    QString loadThisTypeOfBoard = ROOTDIR;
    QString loadThisFromWeb = WEBDEFAULTURL;
    switch (_grpGridSize->checkedId())
    {
    case 0:
        loadThisTypeOfBoard.append("9x9/");
        loadThisFromWeb.append(WEB9X9URL);
        break;
    case 1:
        loadThisTypeOfBoard.append("13x13/");
        loadThisFromWeb.append(WEB13X13URL);
        break;
    case 2:
        loadThisTypeOfBoard.append("17x17/");
        loadThisFromWeb.append(WEB17X17URL);
        break;
        // Never end up here //
    default:
        throw(QString ("something went wrong while computing user lever choice"));
    }
    switch (_grpDifficulty->checkedId())
    {
    case 0:
        loadThisTypeOfBoard.append("easy/");
        loadThisFromWeb.append(WEBDIFFICULTYURL);
        loadThisFromWeb.append('1');
        break;
    case 1:
        loadThisTypeOfBoard.append("medium/");
        loadThisFromWeb.append(WEBDIFFICULTYURL);
        loadThisFromWeb.append('3');
        break;
    case 2:
        loadThisTypeOfBoard.append("hard/");
        loadThisFromWeb.append(WEBDIFFICULTYURL);
        loadThisFromWeb.append('4');
        break;
        // Never end up here //
    default:
        throw(QString ("something went wrong while computing user lever choice"));
    }

    if (!loadThisTypeOfBoard.isEmpty())
    {
        switch(_boardSelector->currentIndex())
        {
        case 0: //Load random level

            if(!_levelFromWeb.isEmpty())
            {
                try
                {
                    qDebug () << "Calling with this url" << loadThisFromWeb;
                    onlineLoad(QUrl(loadThisFromWeb));
                }catch(QString ERRORCODE)
                {
                    qDebug () << ERRORCODE;
                }
            }
            // never end up here but just in case... //
            else
            {
                qDebug() << "No response or no quality of response from web, loading default offline ";
                loadThisTypeOfBoard.append("level1.hashiboard");
                _logic->loadGameBoardFromFile(loadThisTypeOfBoard);
            }

            break;
        case 1:
            loadThisTypeOfBoard.append("level1.hashiboard");
            _logic->loadGameBoardFromFile(loadThisTypeOfBoard);
            break;
        case 2:
            loadThisTypeOfBoard.append("level2.hashiboard");
            _logic->loadGameBoardFromFile(loadThisTypeOfBoard);
            break;
        case 3:
            loadThisTypeOfBoard.append("level3.hashiboard");
            _logic->loadGameBoardFromFile(loadThisTypeOfBoard);
            break;
        case 4:
            loadThisTypeOfBoard.append("level4.hashiboard");
            _logic->loadGameBoardFromFile(loadThisTypeOfBoard);
            break;
        case 5:
            loadThisTypeOfBoard.append("level5.hashiboard");
            _logic->loadGameBoardFromFile(loadThisTypeOfBoard);
            break;
        case 6:
            loadThisTypeOfBoard.append("level6.hashiboard");
            _logic->loadGameBoardFromFile(loadThisTypeOfBoard);
            break;
        case 7:
            loadThisTypeOfBoard.append("level7.hashiboard");
            _logic->loadGameBoardFromFile(loadThisTypeOfBoard);
            break;
        default:
            break;
        }
        qDebug() << "User level choice:" << loadThisTypeOfBoard;
    }
}

void Hashlife::onlineLoad(QUrl urlToSite)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    if (urlToSite != QUrl(IPTESTURL))
    {
        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));
    }
    else
    {
        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFromInternetTesting(QNetworkReply*)));
    }
    QNetworkRequest request;
    request.setUrl(urlToSite);
    request.setRawHeader("Connection", "close");
    manager->get(request);

}

void Hashlife::checkInternetConnection()
{
    onlineLoad(QUrl(IPTESTURL));
}
void Hashlife::checkWebLoadingEngine()
{
    QString makeDefaultURL = WEBDEFAULTURL;
    makeDefaultURL.append(WEB9X9URL);
    onlineLoad(QUrl(makeDefaultURL));
}


void Hashlife::parseSiteData(QString dataFromSite)
{
    QByteArray result = "";
    QString playingLevelID = "";
// regexp to make level string //
    QRegularExpression checkForNode ("(ring)|(white)");
    QRegularExpression checkBoardID ("(puzzle number:)");
    QRegularExpressionMatchIterator match;
    QRegularExpressionMatch foundNode;
// regexp to validate quality of levelstring //
    QRegularExpression checkForDigit ("\\d");
    QRegularExpressionMatchIterator foundDigit;
    QRegularExpressionMatch matchDigit;




// extra info level id //
    QRegularExpressionMatch matchFoundBoardID;

    matchFoundBoardID = checkBoardID.match(dataFromSite);
    if (matchFoundBoardID.hasMatch())
    {   // hopefully stores level id (this should be done using regexp instead) //
        for (int i = 1;i < 7;++i)
        {
            playingLevelID.append(dataFromSite[matchFoundBoardID.capturedEnd()+i]);
        }
    }
    match = checkForNode.globalMatch(dataFromSite);
    while (match.hasNext())
    {
        foundNode = match.next();
        if(foundNode.captured() == "white")
        {
            result.append("0");
            continue;
        }
        result.append(dataFromSite.at((foundNode.capturedEnd()+2)));
    }
    qDebug() << "Level from site loaded " << sqrt(result.length()) << "X"  << sqrt(result.length()) << "=" << result.length();
    qDebug() << playingLevelID << result;


   foundDigit = checkForDigit.globalMatch(result);
   int foundDigits = 0;
   while(foundDigit.hasNext())
   {
        matchDigit = foundDigit.next();
       ++foundDigits;
   }

   if ((foundDigits == result.length()) && ((result.length() == 81) || (result.length() == 169) || (result.length() == 289 )))
   {
    qDebug() << "String looks good!";
    if (_levelFromWeb.isEmpty())
    {
         _levelFromWeb = result;
    }
    else
    {
          // make call //
        _logic->loadLevel(result);
    }
   }


   else
   {
       _levelFromWeb = "";
       qDebug() << "dirty string not loading";
   }








}

void Hashlife::replyFinished(QNetworkReply *reply)
{

    QString dataFromSite = "";
    if(reply->error() == QNetworkReply::NetworkError::NoError)
    {
        if (_clientIP.isEmpty())
        {
            qDebug() << "this client surely has internet although im told otherwise";
        }
        QByteArray readSite = reply->readAll();

        // throw away data before viable data//
        for (int i = 7000; i < readSite.length(); ++i)
        {
            dataFromSite += readSite[i];
        }
        qDebug() << "Downloaded map data from server OK!" << reply->errorString();
        // make call to parser to make use of this information //
        parseSiteData(dataFromSite);
        reply->deleteLater();
    }
    else
    {
        qDebug() << "something wrong with GET request, going offline";
    }

}
void Hashlife::replyFromInternetTesting(QNetworkReply* reply)
{
    _clientIP = reply->readAll();
    if (!_clientIP.isEmpty())
    {
        qDebug() << "Internet connection found at" << _clientIP;
    }
    else
    {
        qDebug() << "internet connection not found";
    }
}
