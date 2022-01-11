# Pirma_Uzduotis_Tvarkinga
# v1.0
* Studentų rūšiavimo į dvi grupes spartos analizė trims kontainerių tipams (vector, list, deque)
* Pirma strategija (v.1.0.1):
  Studentų kontainerio rūšiavimas į du to paties tipo konteinerius (tas pats studentas yra dviejuose konteineriuose)
* Testvimas atliktas su 10 pažymių:
![1 0 1](https://user-images.githubusercontent.com/90559062/148958799-a550092b-e7fe-4803-b95f-6df2ab5ec803.png)


* Antra strategija (v.1.0.2):
  Studentų konteinerio rūšiavimas panaudojant tik vieną naują konteinerį (jei studento galutinis pažymys mažensnis nei 5, jis perkeliamas į naują konteinerį ir       ištrinamas iš bendrojo konteinerio)
* Testvimas atliktas su 10 pažymių:
![1 0 2](https://user-images.githubusercontent.com/90559062/148958914-8bcf79f6-2cf6-45a4-97b7-0b3117694368.png)


* Antroje startegijoje panaudoti algoritmai paspartinti rūšiavimą:
1) remove_if;
2) copy_if;
3) stable_partition;
4) copy_n.
