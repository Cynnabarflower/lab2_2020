#include "HashMap.h"
#include "mainwindow.h"
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{

    auto map = HashMap<Codon, Amino>();
       map.put("k1" ,Amino("a"));
       map.put(Codon("k2") ,Amino("bb"));
       auto map2 = HashMap<Codon, Amino>(map);
       map2.put(Codon("k3"), Amino("ccc"));
       map2.put(Codon("k1"), Amino("aa"));
       assert(map["k2"] == map2["k2"]);
       assert(map["k1"] != map2["k1"]);
       map["k1"] = Amino("aa");
       assert(map["k1"] == map2["k1"]);
       assert(map.size() == 2);
       map.clear();
       assert(map.size() == 0);
       map2.remove("k1");
       assert(map2.size() == 2);
       assert(map2.contains("k2"));
       assert(!map2.contains("k1"));
       map.put("k1", "v1");
       map.put("k4", "v4");
       vector<Codon> keys{ "k1", "k4" };
       auto values = map.get(keys);
       assert(values.size() == 2 && values[0] == "v1" && values[1] == "v4");
       map.saveToFile("file");
       map2.clear();
       map2.loadFromFile("file");
       assert(map == map2);

       std::cout << "Well done!" << std::endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
