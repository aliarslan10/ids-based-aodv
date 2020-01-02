//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package ali_aodv;

simple Dugum
{
    parameters:
        int dugumSayisi;
        bool askGratuitousRREP = default(false); //RFC 3561: 6.6.3 (gereksiz RREP hedef düğüme giden yolda bir sonraki atlamaya gönderilir, sanki hedef düğüm kaynak düğüm için bir RREQ yayınlamış gibi ve bu RREP,  (hayali) RREQ'ye yanıt olarak üretilmiştir.)
        bool useHelloMessages = default(false); // RFC 3561: 6.9
        bool useLocalRepair = default(false); //   RFC 3561: 6.12 (ihtiyac duyularsa yapilacak)

 	    //jitter : sapma, gecikme. örneğin broadcast ve rrep için uygulanabilir.

        @display("i=block/circle");
    gates:
        input girisCikis @diretIn @loose;
	    // @loose : çalışma esnasında hatayı engellemek için bağlantı kontrolünü kapatıyor. (allowunconnected anahtar kelimesi gibi) 
	    // @directIn : sendDirect() ile mesaj alabilmek için var olan giriş kapıları ile belirtilir.
}
