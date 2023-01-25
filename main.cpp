/*
author: Demet Demir - 1921221024 - demet.demir@stu.fsm.edu.tr
assignment: Proje 3
date: 08.01.2023
motivation: C++ dilinde sýnýf yapýsý ve nesne yönelimli programlama
özelliklerini kullanarak problem çözme
*/

#include <iostream>

#include <vector>


using namespace std;

class Film { //Film nesnesi olusturuldu
  private: //private olarak bazi ozellikler eklendi
    string ad;
  int fiyat;
  int adet;
  string cikisTarihi;
  int yasSiniri;
  public:
    //yapici ve yikici metotlar
    Film(string a, int f, int ad, string ct): ad(a),
  fiyat(f),
  adet(ad),
  cikisTarihi(ct) {}
  ~Film() {}
  //ve Film nesnesine ait bazi metotlar (getter,setter etc)
  string getAd() const {
    return ad;
  }
  int getFiyat() const {
    return fiyat;
  }
  int getAdet() const {
    return adet;
  }
  string getCikisTarihi() const {
    return cikisTarihi;
  }
  void setAd(string a) {
    ad = a;
  }
  void setFiyat(int f) {
    fiyat = f;
  }
  void setAdet(int ad) {
    adet = ad;
  }
  void setCikisTarihi(string ct) {
    cikisTarihi = ct;
  }
  int getYasSiniri() const {
    return yasSiniri;
  }
  void setYasSiniri(int ys) {
    yasSiniri = ys;
  }
};
class KorkuFilm: public Film { //Film sinifindan kalitim alan KorkuFilm adinda baska bir sinif
  //bu sinifta yas siniri bulunmakta
  private: int yasSiniri;
  public:
    //yapici ve yikici metotlar -film sinifindan kalitim alir, ekstra olarak yas siniri barindirir
    KorkuFilm(string a, int f, int ad, string ct, int ys): Film(a, f, ad, ct),
  yasSiniri(ys) {}
  ~KorkuFilm() {}
  //getter ve setter metotlari
  int getYasSiniri() const {
    return yasSiniri;
  }
  void setYasSiniri(int ys) {
    yasSiniri = ys;
  }
};

class RomantikFilm: public Film { //Yine Film sinifindan kalitim alan RomantikFilm sinifi
  //bu sinifta ekstra olarak bir sey tanimlanmadi
  //ata sinifinda bulunan ozellikleri aldi sadece
  public: RomantikFilm(string a, int f, int ad, string ct): Film(a, f, ad, ct) {}
    ~RomantikFilm() {}
};

class BilimKurguFilm: public Film { //BilimKurgu Turundeki filmleri barindiran baska bir sinif daha
  public: BilimKurguFilm(string a, int f, int ad, string ct): Film(a, f, ad, ct) {}
    ~BilimKurguFilm() {}
};

class DramFilm: public Film { //Dram Filmlerini barindirab bir diger class, yine Film sinifindan kalitim aldi
  public: DramFilm(string a, int f, int ad, string ct): Film(a, f, ad, ct) {}
    ~DramFilm() {}
};
class Musteri { //Musteri nesnesi olusturuldu
  private: //bazi private ve public ozellikler eklendi
    string ad;
  int yas;
  int bakiye;
  Film * film;
  vector < Film * > oncedenKiraladiklar; //onceden kiraladiklari filmleri tutan vector veri yapisi
  Film * suAnkiKiralama;
  //Film sinifina erisim icin (getter ve setter metotlarina erisim) pointer tutuldu
  public:
    //yapici metot
    Musteri(string ad, int yas): ad(ad),
  yas(yas) {}
  //Yikici metot
  ~Musteri() {}
  // Diger metotlar
  void setBakiye(int b) {
    bakiye = b;
  }
  int getBakiye() {
    return bakiye;
  }
  string getAd() const {
    return ad;
  }
  void setAd(string ad) {
    this -> ad = ad;
  }
  int getYas() const {
    return yas;
  }
  void setYas(int yas) {
    this -> yas = yas;
  }
  vector < Film * > getOncedenKiraladiklar() const {
    return oncedenKiraladiklar;
  }
  void setOncedenKiraladiklar(vector < Film * > oncedenKiraladiklar) {
    this -> oncedenKiraladiklar = oncedenKiraladiklar;
  }
  Film * getSuAnkiKiralama() const {
    return suAnkiKiralama;
  }
  void setSuAnkiKiralama(Film * suAnkiKiralama) {
    this -> suAnkiKiralama = suAnkiKiralama;
  }
  Film * getFilm() const {
    return film;
  }
  void setFilm(Film * film) {
    this -> film = film;
  }

  void oncedenKiraladiklariniGoster() const {
    // Onceden kiraladiklarimizin yoklugunu kontrol edin
    if (oncedenKiraladiklar.empty()) {
      cout << "Onceden kiralamis oldugunuz film yok" << endl;
    } else {
      // Onceden kiraladiklarimizi gosterin
      cout << "Onceden kiralamis oldugunuz filmler:" << endl;
      for (const auto & film: oncedenKiraladiklar) {
        cout << film -> getAd() << " - " << film -> getFiyat() << endl;
      }
    }
  }
  void oncedenKiraladiklariEkle(Film * film) {
    oncedenKiraladiklar.push_back(film);
  }
};
class Kiralama { //Kiralama sinifi, burada kiralama islemleri gerceklesecek
  private: Musteri * musterinin; //Musteri nesnesi olusturuldu
  Film * filmin; //Film nesnesi olusturuldu
  int fiyat; //ve fiyat bilgisi alindi
  int stokDurumu;
  public:
    /*
    Burada 4 farkli film cesidi icin 4 tane Kiralama metodunu override ettim
    Bazi filmlerde ayricalikli islemler yapilacak 
    Ornegin Korku Filmi icin 18 yas siniri kontrolu
    Romantik Filmler icin 2 uzeri kiralamalarda indirimli olacak
    */

    Kiralama(Musteri & m, RomantikFilm & f): musterinin( & m),
  filmin( & f) {
    //Fiyat bilgisi basta tutulur
    fiyat = filmin -> getFiyat();
    stokDurumu = filmin -> getAdet();
    cout << musterinin -> getAd() << " isimli musteri icin: " << filmin -> getAd() << " isimli film: " << endl;
    //2 ve uzeri kiralamalarda indirim uygulanir
    //her bir if blogu icinde musterinin bakiye bilgisi ve stok surumu kontrol edilir.
    if (musterinin -> getOncedenKiraladiklar().size() >= 2 && musterinin -> getBakiye() >= 0.5 * fiyat && filmin -> getAdet() != 0) {
      fiyat = 0.5 * fiyat;
      musterinin -> setSuAnkiKiralama(filmin);
      musterinin -> setBakiye(musterinin -> getBakiye() - 0.5 * fiyat);
      //onceden kiralamalara eklenir
      musterinin -> oncedenKiraladiklariEkle(filmin);
      filmin -> setAdet(stokDurumu - 1);
      cout << "3. kiralama sonucunda %50 indirim basariyla uygulandi." <<
        "Stok Durumu: " << stokDurumu << " Bakiye: " << musterinin -> getBakiye() << endl;
    } else {
      //24 yas ve alti ogrenci kabul edilir, ve stok musaitse kiralama %10 indirimle gerceklesir
      if (musterinin -> getYas() < 24 && filmin -> getAdet() != 0 && musterinin -> getBakiye() >= 0.9 * fiyat) {
        fiyat = 0.9 * fiyat;
        musterinin -> setSuAnkiKiralama(filmin);
        musterinin -> setBakiye(musterinin -> getBakiye() - fiyat);
        musterinin -> oncedenKiraladiklariEkle(filmin);
        filmin -> setAdet(stokDurumu - 1);
        cout << "Ogrenci indirimi uygulandi, film basariyla kiralandi." <<
          "Stok Durumu: " << stokDurumu << " Bakiye: " << musterinin -> getBakiye() << endl;

      }
      //24 yas uzeri icin standart fiyat uygulanir
      else if (filmin -> getAdet() != 0 && musterinin -> getBakiye() >= fiyat) {
        musterinin -> setSuAnkiKiralama(filmin);
        musterinin -> setBakiye(musterinin -> getBakiye() - fiyat);
        musterinin -> oncedenKiraladiklariEkle(filmin);
        filmin -> setAdet(stokDurumu - 1);
        cout << "Film Kiralandi." <<
          "Stok Durumu: " << stokDurumu << " Bakiye: " << musterinin -> getBakiye() << endl;
      }
      //bakiye yetersiz ise uyari mesaji verir
      else if (filmin -> getAdet() != 0) {
        cout << musterinin -> getAd() << " isimli musteri icin bakiye yetersiz !!" << endl;
      }
      //stokta bulunmamasi halinde uyari mesaji verir
      else {
        cout << filmin -> getAd() << " isimli film STOKTA YOK." << endl;
      }
    }
  }
  Kiralama(Musteri & m, DramFilm & f): musterinin( & m),
  filmin( & f) {

    fiyat = filmin -> getFiyat();
    stokDurumu = filmin -> getAdet();
    cout << musterinin -> getAd() << " isimli musteri icin: " << filmin -> getAd() << " isimli film: " << endl;
    //24 yas ve alti ogrenci kabul edilir, ve stok musaitse kiralama %10 indirimle gerceklesir
    if (musterinin -> getYas() < 24 && filmin -> getAdet() != 0 && musterinin -> getBakiye() >= 0.9 * fiyat) {
      fiyat = 0.9 * fiyat;
      musterinin -> setSuAnkiKiralama(filmin);
      musterinin -> setBakiye(musterinin -> getBakiye() - fiyat);
      musterinin -> oncedenKiraladiklariEkle(filmin);
      cout << "Ogrenci indirimi uygulandi, film basariyla kiralandi." <<
        "Stok Durumu: " << stokDurumu << " Bakiye: " << musterinin -> getBakiye() << endl;

    }
    //24 yas uzeri icin standart fiyat uygulanir
    else {
      if (filmin -> getAdet() != 0 && musterinin -> getBakiye() >= fiyat) {
        musterinin -> setSuAnkiKiralama(filmin);
        musterinin -> oncedenKiraladiklariEkle(filmin);
        musterinin -> setBakiye(musterinin -> getBakiye() - fiyat);
        cout << "Film Kiralandi." <<
          "Stok Durumu: " << stokDurumu << " Bakiye: " << musterinin -> getBakiye() << endl;

      }
      //bakiye yetersiz ise uyari mesaji verir
      else if (filmin -> getAdet() != 0) {
        cout << musterinin -> getAd() << " isimli musteri icin bakiye yetersiz !!" << endl;
      }
      //stokta bulunmamasi halinde uyari mesaji verir
      else {
        cout << filmin -> getAd() << " isimli film STOKTA YOK." << endl;
      }
    }

  }
  Kiralama(Musteri & m, BilimKurguFilm & f): musterinin( & m),
  filmin( & f) {
    // Ã–grenciye %10 indirim uygulama
    fiyat = filmin -> getFiyat();
    stokDurumu = filmin -> getAdet();
    cout << musterinin -> getAd() << " isimli musteri icin: " << filmin -> getAd() << " isimli film: " << endl;
    //24 yas ve alti ogrenci kabul edilir, ve stok musaitse kiralama %10 indirimle gerceklesir
    if (musterinin -> getYas() < 24 && filmin -> getAdet() != 0 && musterinin -> getBakiye() >= 0.9 * fiyat) {
      fiyat = 0.9 * fiyat;
      musterinin -> setSuAnkiKiralama(filmin);
      musterinin -> oncedenKiraladiklariEkle(filmin);
      musterinin -> setBakiye(musterinin -> getBakiye() - fiyat);
      cout << "Ogrenci indirimi uygulandi, film basariyla kiralandi." <<
        "Stok Durumu: " << stokDurumu << " Bakiye: " << musterinin -> getBakiye() << endl;

    } else {
      //24 yas uzeri icin standart fiyat uygulanir
      if (filmin -> getAdet() != 0 && musterinin -> getBakiye() >= fiyat) {
        musterinin -> setSuAnkiKiralama(filmin);
        musterinin -> oncedenKiraladiklariEkle(filmin);
        musterinin -> setBakiye(musterinin -> getBakiye() - fiyat);
        cout << "Film Kiralandi." <<
          "Stok Durumu: " << stokDurumu << " Bakiye: " << musterinin -> getBakiye() << endl;
      }
      //bakiye yetersiz ise uyari mesaji verir
      else if (filmin -> getAdet() != 0) {
        cout << musterinin -> getAd() << " isimli musteri icin bakiye yetersiz !!" << endl;
      }
      //stokta bulunmamasi halinde uyari mesaji verir
      else {
        cout << filmin -> getAd() << " isimli film STOKTA YOK." << endl;
      }

    }
  }
  Kiralama(Musteri & m, KorkuFilm & f): musterinin( & m),
  filmin( & f) {

    fiyat = filmin -> getFiyat();
    stokDurumu = filmin -> getAdet();
    cout << musterinin -> getAd() << " isimli musteri icin: " << filmin -> getAd() << " isimli film: " << endl;
    //Musterinin yasi kontrol edilir 18 den asagisina korku filmi satilamaz
    if (musterinin -> getYas() < filmin -> getYasSiniri()) {
      cout << "Musteri yasi 18'in altindadir, film kiralama basarisiz." << endl;
    } else {
      if (filmin -> getAdet() != 0 && musterinin -> getYas() >= 18 && musterinin -> getBakiye() >= fiyat) {
        musterinin -> setSuAnkiKiralama(filmin);
        musterinin -> oncedenKiraladiklariEkle(filmin);
        cout << "Film Kiralandi." <<
          "Stok Durumu: " << stokDurumu << " Bakiye: " << musterinin -> getBakiye() << endl;

      } else if (filmin -> getAdet() != 0) {
        cout << musterinin -> getAd() << " isimli musteri icin bakiye yetersiz !!" << endl;
      } else {
        cout << filmin -> getAd() << " isimli film STOKTA YOK." << endl;
      }
    }
  }
  // Diger metotlar
  Musteri * getMusteri() const {
    return musterinin;
  }
  Film * getFilm() const {
    return filmin;
  }
  int getFiyat() const {
    return fiyat;
  }
};

class Magaza { //Magaza nesnesi olusturdum
  private:
    //bu magazaya ait musteriler ve filmler adinda vektorler olusturdum
    std::vector < Musteri > musteriler;
  std::vector < Film > filmler;

  public: Magaza() {}
  //musteriler vektorune eleman ekleyen metot:
  void musteriEkle(Musteri m) {
    musteriler.push_back(m);
  }
  //musteriler vektorunde, parametre olarak gonderilen 
  //musteri tipindeki nesne, aranmaya baslar
  void musteriSil(Musteri m) {
    for (int i = 0; i < musteriler.size(); i++) {
      //eger musteri vektorun icinde varsa
      if (musteriler[i].getAd() == m.getAd()) {
        //bu musteri silinir
        musteriler.erase(musteriler.begin() + i);
        break;
      }
    }
  }
  //musteriler vektorunun size'i alinarak musteri sayisi donduren fonksiyon
  int musteriSayisi() {
    return musteriler.size();
  }
  //parametre olarak film tipinden nesne alir
  void filmEkle(Film f) {
    //boolean bir degisken tutulur, basta false degeri atanir
    bool varMi = false;
    //filmler vektoru for dongusuyle aranir
    for (int i = 0; i < filmler.size(); i++) {
      //eger parametredeki filmin adi, listedeki filmin adina esitse
      if (filmler[i].getAd() == f.getAd()) {
        //bu filmin adet'i 1 arttirilir
        filmler[i].setAdet((filmler[i].getAdet()) + f.getAdet());
        varMi = true;
        break;
      }
    }
    //yoksa, vektore yeni filmi ekler
    if (!varMi) {
      filmler.push_back(f);

    }
  }

  //musteri filmi iade etmek istediginde:
  void filmIadeEt(Film f) {
    //filmler vektorunun icinde for dongusuyle gezilir
    for (int i = 0; i < filmler.size(); i++) {
      //parametre olarak gonderilen filmin adi
      //vektordeki filmin adina esitse
      if (filmler[i].getAd() == f.getAd()) {
        //adet sayisi 1 arttirilir
        filmler[i].setAdet(filmler[i].getAdet() + 1);
        break;
      } else {
        //esit degilse, yani stogu tukenmis bir filmi iade etmek istiyorsa
        filmEkle(f);
      }
    }
  }
  //film sayisini donduren metot
  int filmSayisi() {
    return filmler.size();
  }

  std::vector < Film > filmleriGetir() {
    return filmler;
  }

  std::vector < Musteri > musterileriGetir() {
    return musteriler;
  }
};
int main() {

  //Musteri tanimlari
  Musteri musteri("Carl Grimes", 18);
  musteri.setBakiye(100);
  Musteri musteri1("Lydia Whisper", 20);
  musteri1.setBakiye(50);
  Musteri musteri2("Coco Espinosa", 10);
  musteri2.setBakiye(10);
  Musteri musteri3("Melissa McBride", 48);
  musteri3.setBakiye(50);
  Musteri musteri4("Maggie Rhee", 36);
  musteri4.setBakiye(25);
  Musteri musteri5("Norman Reedus", 49);
  musteri5.setBakiye(50);
  //Magaza nesnesi olusturma
  Magaza magaza;
  //bu nesneye musteri ekleme:
  magaza.musteriEkle(musteri);
  magaza.musteriEkle(musteri1);
  magaza.musteriEkle(musteri2);
  magaza.musteriEkle(musteri3);
  magaza.musteriEkle(musteri4);
  magaza.musteriEkle(musteri5);

  //Film tanimlari 
  KorkuFilm korku0("Korku Seansi", 10, 2, "2022-01-01", 18);
  KorkuFilm korku1("Tepedeki Ev", 15, 1, "2022-01-01", 18);
  KorkuFilm korku2("Gozlerinin Ardinda", 20, 1, "2022-01-01", 18);

  BilimKurguFilm bk0("Interstellar", 10, 2, "2022-01-01");
  BilimKurguFilm bk1("Labirent", 10, 1, "2022-01-01");
  BilimKurguFilm bk2("Aclik Oyunlari", 10, 5, "2022-01-01");

  RomantikFilm romantik0("Senden Once Ben", 20, 2, "2022-01-01");
  RomantikFilm romantik1("Ask ve Gurur", 6, 1, "2022-01-01");
  RomantikFilm romantik2("When Harry Met Sally", 10, 1, "2022-01-01");

  //Ayni filmleri stoga ekleme:
  DramFilm dram0("Esaretin bedeli", 10, 2, "2022-01-01");
  DramFilm dram1("Esaretin bedeli", 10, 8, "2022-01-01");
  DramFilm dram2("Esaretin bedeli", 10, 2, "2022-01-01");
  //beklenen cikti: Esaretin bedeli: 12
  magaza.filmEkle(dram0);
  magaza.filmEkle(dram1);
  magaza.filmEkle(dram2);
  //diger turler de magazaya eklenir
  magaza.filmEkle(korku0);
  magaza.filmEkle(korku1);
  magaza.filmEkle(korku2);
  magaza.filmEkle(bk0);
  magaza.filmEkle(bk1);
  magaza.filmEkle(bk2);
  magaza.filmEkle(romantik0);
  magaza.filmEkle(romantik1);
  magaza.filmEkle(romantik2);

  cout << "Musteri sayisi: " << magaza.musteriSayisi() << endl;
  cout << "Film sayisi: " << magaza.filmSayisi() << endl;

  vector < Musteri > musteriler = magaza.musterileriGetir();
  cout << "Musteriler Isim Soyisim: " << endl;
  for (int i = 0; i < musteriler.size(); i++) {
    cout << musteriler[i].getAd() << endl;
  }
  vector < Film > filmler = magaza.filmleriGetir();
  cout << "Filmler ve Stok Durumu Sirasiyla: " << endl;
  for (int i = 0; i < filmler.size(); i++) {
    cout << filmler[i].getAd() << " : " << filmler[i].getAdet() << endl;
  }
  //Kiralama islemini 3 kez yapan musteri 2 stogu bulunan filmde, 3. kiralamada hata alacaktir.

  Kiralama k1(musteri, romantik0);
  Kiralama k2(musteri1, romantik0);
  //musteri3 kiralama islemi yapamaz.Stok yok uyarisi alir.
  Kiralama k3(musteri3, romantik0);
  magaza.filmIadeEt(romantik0);
  //Farkli filmler icin kiralama:
  Kiralama k4(musteri2, korku0);
  Kiralama k5(musteri1, korku0);

  return 0;
}
