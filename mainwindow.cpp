#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Song.h"
#include "Graph.h"

#include <QtCore>
#include <QtGui>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>
#include <set>
#include <stack>
#include <queue>
#include <fstream>
#include <iomanip>

using namespace std;

unsigned int hashFunction(char const* key, int table_size) {
    unsigned int hashCode = 0;
    unsigned int b = 0;


    //Traverse the character array from left to right (from 0 index to the end of the array):
    unsigned int lengthOfKey = sizeof(key)/sizeof(char);

    int index = 0;
    while (key[index] != '\0')
    {
        //If n is even:
        if (index % 2 == 0)
        {
            b = (hashCode << 7) ^ key[index] ^ (hashCode >> 3);

        }
        else //If n is odd:
        {
            b = (hashCode << 11) ^ key[index] ^ (hashCode >> 5);
            b = ~ b;

        }
        hashCode = hashCode ^ b;
        index++;
    }



    //Traverse end and set the leftmost bit to 0. (i.e., set the 32nd bit to 0)
    int mask = 0; //creates int set to 0
    mask = ~mask; //reverses
    mask = mask >> 1;
    hashCode = hashCode & mask;

    hashCode = hashCode % table_size;


    return hashCode;
}




vector<Song> GetDataFromCSVFile(string filePath){
    std::ifstream inFile(filePath);

    vector<Song>temp;
    if(inFile.is_open())
    {
        //heading of file
        //Country,Continent,Rank,Title,Artists,Album,Explicit,Duration
        string lineFromFile;
        getline(inFile, lineFromFile);

        //first line
        while (getline(inFile, lineFromFile))
        {
            std::istringstream stream(lineFromFile); //stream of data coming from first line

            string country;
            string continent;
            string tempRank;
            string title;
            string artists;
            string album;
            string Explicit;
            string duration;
            unsigned int rank;


            //Country,Continent,Rank,Title,Artists,Album,Explicit,Duration

            getline(stream, country, ',');
            getline(stream, continent, ',');
            getline(stream, tempRank, ',');
            getline(stream, title, ',');
            getline(stream, artists, ',');
            getline(stream, album, ',');
            getline(stream, Explicit, ',');
            getline(stream, duration, ' ');


            rank = stoi(tempRank);

            //Song(string songName, string songArtist, string country_, string continent_, int rank_, string duration_)
            Song song(title,  artists, country, continent, rank, duration);
            temp.push_back(song);
        }

    }

    else{
        cout << "file is not open" << endl;
    }
    return temp;

}

Graph temp(vector<Song>& S){
    Graph g;
    return g;
}

//creat graph for every continent or country
//pass in a string of country and include while loop of if s[i].country == country
Graph loadGraphforCountry(Graph& g, vector<Song>& s, string country)
{
    g.Clear();

    int from, to, weight, i = 0;

    for (i = 0; i < s.size(); i++)
    {
        if (s[i].country == country)
            break;
    }

    while (s[i].country == country)
    {
        from = hashFunction(s[i].title.c_str(), 50);
        to = hashFunction(s[i+1].title.c_str(), 50);

        if(i != s.size()-1)
            g.insertEdge(from, to, s[i].rank, s[i]);
        else
            g.insertEdge(from, from, s[i].rank, s[i]);

        i++;
    }

return g;

    //hash the song name and load into vector (this will the "to" & "from")
    //weight: ranking of the song ... load into vector
}

//creat graph for every continent or country
//pass in a string of country and include while loop of if s[i].country == country
Graph loadGraphforContinent(Graph& g, vector<Song>& s, string continent)
{
    g.Clear();

    int from, to, weight, i = 0;

    for (i = 0; i < s.size(); i++)
    {
        if (s[i].continent == continent)
            break;
    }

    while (s[i].continent == continent){
        from = hashFunction(s[i].title.c_str(), 50);
        to = hashFunction(s[i+1].title.c_str(), 50);

        if(i != s.size()-1)
            g.insertEdge(from, to, s[i].rank, s[i]);
        else
            g.insertEdge(from, from, s[i].rank, s[i]);

        i++;
    }

    return g;

}


Graph loadGraph(Graph& g, vector<Song>& s){
    g.Clear();
    int from, to, weight;
    for (int i = 0; i < s.size(); i++)
    {
        from = hashFunction(s[i].title.c_str(), 100);
        to = hashFunction(s[i+1].title.c_str(), 100);
        if(i != s.size()-1)
            g.insertEdge(from, to, s[i].rank, s[i]);
        else
            g.insertEdge(from, from, s[i].rank, s[i]);
    }

    return g;
}




MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QPixmap bkgnd("/Users/meghan.ka/Downloads/sun.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    QPalette::Window;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

   // ui->searchCont->setStyleSheet("/Users/meghan.ka/Downloads/contB.png");

    ui->continentDrop->addItem("Africa");
    ui->continentDrop->addItem("Asia");
    ui->continentDrop->addItem("South America");
    ui->continentDrop->addItem("North America");
    ui->continentDrop->addItem("Europe");
    ui->continentDrop->addItem("Australia");

    ui->songContDrop->addItem("5");
    ui->songContDrop->addItem("10");
    ui->songContDrop->addItem("20");
    ui->songContDrop->addItem("30");


    ui->countryBox->addItem("Argentina");
    ui->countryBox->addItem("Australia");
    ui->countryBox->addItem("Austria");
    ui->countryBox->addItem("Belgium");
    ui->countryBox->addItem("Bolivia");
    ui->countryBox->addItem("Brazil");
    ui->countryBox->addItem("Bulgaria");
    ui->countryBox->addItem("Canada");
    ui->countryBox->addItem("Chile");
    ui->countryBox->addItem("Colombia");
    ui->countryBox->addItem("Costa Rica");
    ui->countryBox->addItem("Czech Republic");
    ui->countryBox->addItem("Denmark");
    ui->countryBox->addItem("Dominican Republic");
    ui->countryBox->addItem("Ecuador");
    ui->countryBox->addItem("El Salvador");
    ui->countryBox->addItem("Estonia");
    ui->countryBox->addItem("Finland");
    ui->countryBox->addItem("France");
    ui->countryBox->addItem("Germany");
   // ui->countryBox->addItem("Global");
    ui->countryBox->addItem("Greece");
    ui->countryBox->addItem("Guatamala");
    ui->countryBox->addItem("Honduras");
    ui->countryBox->addItem("Hong Kong");
    ui->countryBox->addItem("Hungary");
    ui->countryBox->addItem("Iceland");
    ui->countryBox->addItem("India");
    ui->countryBox->addItem("Indonesia");
    ui->countryBox->addItem("Ireland");
    ui->countryBox->addItem("Israel");
    ui->countryBox->addItem("Italy");
    ui->countryBox->addItem("Japan");
    ui->countryBox->addItem("Latvia");
    ui->countryBox->addItem("Lithuania");
    ui->countryBox->addItem("Luxembourg");
    ui->countryBox->addItem("Malaysia");
    ui->countryBox->addItem("Malta");
    ui->countryBox->addItem("Mexico");
    ui->countryBox->addItem("Netherlands");
    ui->countryBox->addItem("New Zealand");
    ui->countryBox->addItem("Nicaragua");
    ui->countryBox->addItem("Norway");
    ui->countryBox->addItem("Panama");
    ui->countryBox->addItem("Paraguay");
    ui->countryBox->addItem("Peru");
    ui->countryBox->addItem("Philippines");
    ui->countryBox->addItem("Poland");
    ui->countryBox->addItem("Portugal");
    ui->countryBox->addItem("Romania");
    ui->countryBox->addItem("Singapore");
    ui->countryBox->addItem("Slovakia");
    ui->countryBox->addItem("South Africa");
    ui->countryBox->addItem("Spain");
    ui->countryBox->addItem("Sweden");
    ui->countryBox->addItem("Switzerland");
    ui->countryBox->addItem("Taiwan");
    ui->countryBox->addItem("Thailand");
    ui->countryBox->addItem("Turkey");
    ui->countryBox->addItem("United Kingdom");
    ui->countryBox->addItem("United States");
    ui->countryBox->addItem("Uruguay");
    ui->countryBox->addItem("Vietnam");

    //QString continentPicked = ->currentText();//gets chosen continent stored in variable
    // QString countryPicked = ->currentText();//gets chosen country stored in variable

    ui->numberBox->addItem("5");
    ui->numberBox->addItem("10");
    ui->numberBox->addItem("20");
    ui->numberBox->addItem("30");


}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_searchCont_clicked(){
    ui->stackedWidget->setCurrentIndex(3);

}


void MainWindow::on_searchCountry_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}





void MainWindow::on_backCountry_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_backCont_clicked(){
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_loadButton_clicked(){//continent{
    QString contChoice = ui->continentDrop ->currentText();
    QString numSongs = ui->songContDrop->currentText();
    vector<Song>tempN;
    string file = "../SpotifyTopSongsByCountry - May 2020 copy.csv";
    tempN = GetDataFromCSVFile(file);
    Graph temp;
    Graph g;
    string str = contChoice.toStdString();
    g = loadGraphforContinent(temp, tempN, str);

    map<int, vector<Graph::Vertex>> sample = g.getNestedMap();

    vector<int> vec = g.getVertices();
    vector<string>hold;

    // is this the var? yes
    int numTemp = numSongs.toInt();
    int indexTemp = 0;
    QByteArray tempS = " ";

    string indexString = to_string(indexTemp);

    for (int element : vec) {
        for (int i = 0; i < sample[element].size(); i++) {
            if (indexTemp < numTemp-1) {
                if(numTemp <= 20){
                    int numT = indexTemp + 1;
                    string indexString = to_string(numT);
                    tempS += indexString +". " + sample[element].at(i).title + " by "+ sample[element].at(i).artist + "\n ";
                }else{
                    int numT = indexTemp + 1;
                    string indexString = to_string(numT);
                    tempS += indexString +". " + sample[element].at(i).title + " by "+ sample[element].at(i).artist + ", ";
                }

                //hold.push_back(sample[element].at(i).title);
                //cout << sample[element].at(i).title << endl;
            }else if(indexTemp < numTemp){

                int numT = indexTemp + 1;
                string indexString = to_string(numT);
                tempS += indexString +". " + sample[element].at(i).title + " by "+ sample[element].at(i).artist;
            }
            indexTemp++;
        }
    }



    ui->stackedWidget->setCurrentIndex(4);
    ui->label_9->setText("You selected " + numSongs+ " songs from " +contChoice);
    ui->playLabel->setText(tempS);
    ui->playLabel->setWordWrap(true);

}


void MainWindow::on_loadCountry_clicked(){//country
    QString countryChoice = ui->countryBox ->currentText();
    QString numSongs = ui->numberBox->currentText();
    vector<Song>tempN;
    string file = "../SpotifyTopSongsByCountry - May 2020 copy.csv";
    tempN = GetDataFromCSVFile(file);
    Graph g;
    Graph temp;
    string str = countryChoice.toStdString();
    g = loadGraphforCountry(temp, tempN, str);

    map<int, vector<Graph::Vertex>> sample = g.getNestedMap();

    vector<int> vec = g.getVertices();
    vector<string>hold;

    // is this the var? yes
    int numTemp = numSongs.toInt();
    int indexTemp = 0;
    QByteArray tempS = " ";

    string indexString = to_string(indexTemp);



    for (int element : vec) {
        for (int i = 0; i < sample[element].size(); i++) {
            if (indexTemp < numTemp-1) {
                if(numTemp <= 20){
                    int numT = indexTemp + 1;
                    string indexString = to_string(numT);
                    tempS += indexString +". " + sample[element].at(i).title + " by "+ sample[element].at(i).artist + "\n ";
                }
                else{
                    int numT = indexTemp + 1;
                    string indexString = to_string(numT);
                    tempS += indexString +". " + sample[element].at(i).title + " by "+ sample[element].at(i).artist + ", ";
                }

                //hold.push_back(sample[element].at(i).title);
                //cout << sample[element].at(i).title << endl;
            }
            else if(indexTemp < numTemp){

                int numT = indexTemp + 1;
                string indexString = to_string(numT);
                tempS += indexString +". " + sample[element].at(i).title + " by "+ sample[element].at(i).artist;
            }
            indexTemp++;
        }
    }


    ui->stackedWidget->setCurrentIndex(4);
    ui->label_9->setText("You selected " + numSongs+ " songs from " +countryChoice);
    ui->playLabel->setText(tempS);
    ui->playLabel->setWordWrap(true);



}


void MainWindow::on_startOver_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


void MainWindow::on_currentLibrary_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_pushButton_clicked(){//dfs
    vector<Song>tempN;
    string file = "../SpotifyTopSongsByCountry - May 2020 copy.csv";
    tempN = GetDataFromCSVFile(file);
    Graph g;
    Graph temp;

    g = loadGraph(temp, tempN);
    int vecSize = g.getVertices().size();
    if (vecSize > 0) {
        // First element in vecSize.
        int originElement;
        originElement = g.getVertices().at(0);
        g.dfs(originElement);
    }
    else {
        // vec is empty
    }


}


void MainWindow::on_pushButton_2_clicked()//bfs
{
    vector<Song>tempN;
    string file = "../SpotifyTopSongsByCountry - May 2020 copy.csv";
    tempN = GetDataFromCSVFile(file);
    Graph g;
    Graph temp;

    g = loadGraph(temp, tempN);
    int vecSize = g.getVertices().size();
    if (vecSize > 0) {
        // First element in vecSize.
        int originElement;
        originElement = g.getVertices().at(0);
        g.bfs(originElement);
    }
    else {
        // vec is empty
    }


}
void MainWindow::on_backAll_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}