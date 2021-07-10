
## **Şebeke Bağlantılı Mikro İnverter 17-06-2016**

### Giriş :
Rüzgar üretim sistemleri ve Fotovoltaik (PV) sistemler gibi yenilenebilir kaynaklar, uygun ve gelecek vaat eden yenilenebilir enerji kaynakları olarak son birkaç yılda büyük bir görünürlük kazanmıştır.

Güneş enerjisi sistemlerine olan talepteki son artış, üretimdeki genel maliyetleri azaltan ve PV panellerin verimliliğini artıran kristal panellerin üretimindeki gelişmelerden kaynaklanmaktadır. Güneş enerjisine olan talebin ek nedenleri şunlardır: PV teknolojisi kanıtlanmış ve güvenilirdir, PV modüllerinin 30 yılı aşan garantileri ve devlet teşvikleri vardır.

Solar inverter sistemleri için iki temel gereksinim vardır: PV panelinden mevcut enerjiyi toplamak ve şebeke gerilimi ile aynı fazda sinüzoidal bir akımı şebekeye enjekte etmek. PV panelden enerjinin hasat edilmesi için bir Maksimum Güç Noktası İzleme (MPPT) algoritması gereklidir. Bu algoritma, herhangi bir zamanda PV modülünden elde edilebilecek maksimum güç miktarını belirler. Şebekeye arayüz, solar inverter sistemlerinin kamu hizmeti şirketleri tarafından verilen belirli standartlara uymasını gerektirir.

Solar Mikro İnverter Referans Tasarımı, tek kademeli, şebeke bağlantılı, solar PV mikro invertördür. Bu, güneş panelinden gelen DC gücünün doğrudan doğruya AC sinyaline dönüştürüldüğü anlamına gelir. Bu dönüştürme, serpiştirilmiş bir geri dönüş dönüştürücüsü tarafından yapılır. 2x hat frekansında anahtarlanan bir Tam Köprü (açılır) dönüştürücü, şebekeye giden güç akışının yönünü kontrol eder. Bu mikro invertör, 25 VDC ila 45 VDC giriş voltajı aralığı ve ~55V maksimum açık devre voltajı ile yaklaşık 250 watt güç derecesine sahip herhangi bir PV modülüne bağlanmak üzere tasarlanmıştır.


### **Projenin Konusu :** 
- Mikro Inverter
- PIC33F mikrodenetleyiciler
- XC16 PIC C Compiler (Derleyic)
- PCB dizayn 
- Fixed Point sayılar ver aritmatiği
- Güç Elektroniği (Buck-Boost Konvertör yapıları)
- Kontrol sistemleri (PID yapıları)
-  Matlab modelleri

### **Not :**

Proje bu haliyle hazırlanan PCB üzerinden donanım testleri tamamlanmış. Basit olarak dışarıdan verilen ayarlı DC gerilimle çıkış voltajı yazılımsal olarak  100V ayarlanarak akkor telli lamba yakılmıştır. 100W çıkış temin edilebilmiştir.

Kontrol yapıları oluşturma şaşmasına geçilemeden proje çalışmaları elde olamayan sebeplarde dolayı sonlandırılmıştır.. Dolayısıyla bu depoda geliştirilen yazılımda kontrol yapıları eksiktir.

Uygulama notunda yer alan kaynak kodlardan yararlanılarak. Uygun yapılar oluşturulabilir.





