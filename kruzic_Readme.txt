3. zadatak - dvostruko klatno

Slika sa zadatka je izvedena tako da je napravljeno dvostruko klatno koristeći kugle (gluSolidSphere) i cilindre (glutCylinder). Cijeli je objekt obješen za gornju kuglicu te se kreću u pravilu kako se gornja kuglica kreće. Dakle ako gornja kuglica ima rotaciju, cijeli će se objekt na isti način rotirati. To je ostvareno pomoću push i pop matrix te se koristi hijerarhski model.

Kut rotacije se mijenja tako da se povećava ili smanjuje za jedan stupanj te svi pomični dijelovi mijenjaju kut za toliko.

Trag nažalost nije ostvaren zbog manjka ideja.

Program se pokreće ne koristeći nikakve argumente.

s - početak animacije
x - zaustavljanje animacije
qwe - mijenjanje osi okretanja gornjeg cilindra
bnm - mijenjanje osi okretanja donjeg cilindra
ESC - izlaz

Reference koje sam koristio:
Laboratorijske vježbe
stackoverflow.com
opengl.org/wiki