# piBotSchakel

Branches:
Wat ik heb geleerd van de video op https://www.youtube.com/watch?v=DSeyfEgoPOM :
In de video wordt alles voorgedaan dus als je mijn gebrabbel niet kan volgen, watch the tutorial.

Git werkt met branches. Branches zijn eigenlijk een soort van mappen waarin onze code staat.
In de praktijk zie je deze mappen niet en werk je altijd in 1 branch.
Standaard is er maar 1 branch die de master branch genoemd wordt.
De master branch is de branch waar de code inzit waar we nu mee bezig zijn en die werkt.

Als er een wijziging aan de code moet gebeuren maak je een nieuwe branch aan (git checkout -b naamVanEenNieuweBrach).
Je kan dit simplistisch gezien vergelijken met het kopieren van de code naar een nieuwe map. In die nieuwe map ga je dan wijzigingen doen aan de code.

Vanaf het moment dat je klaar bent met het wijzigen van de code (het programma compileert en werkt zoals verwacht) kan de code terug gekopieerd worden naar de master branch (de map waar de originele code staat).
Dit doe je met een merge (git merge naamVanEenNieuweBrach).
Als er een conflict gebeurd door het mergen kan dit opgelost worden met 'git mergetool', je krijgt dan een grafische interface met de verschillen die git niet kan oplossen. Je moet dan zelf kiezen welke versie van de file je wil behouden.

Voordat er grote wijzigingen gebeuren aan de master branch kan er best een tag gemaakt worden.
Een tag is een kopie van de master branch die gemaakt kan worden na een commit.
Als je bijvoorbeeld net een nieuwe functionaliteit hebt toegevoegd kan je hier een tag van maken zodat je dit later terug kan bekijken.
