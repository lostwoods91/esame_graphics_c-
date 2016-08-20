Librerie esterne utilizzate:

- Simple DirectMedia Layer (SDL): gestione degli eventi e della finestra dell'applicazione;
- OpenGL Mathematics (GLM): libreria grafica basata su GLSL;
- OpenGL Extension Wrangler Library (GLEW): estensione per le funzioni openGL;
- stb_image.h: per la lettura delle texture in formato .bmp

Ulteriori fonti:

- http://www.learnopengl.com/#!In-Practice/2D-Game/Collisions/Collision-Detection per l'individuazione delle collisioni;
- https://github.com/SFML/SFML/wiki/Source:-Particle-System per la creazione di un particle system;
- https://github.com/mtarini/kamikazeLab per la gestione della finestra e degli eventi e
	per le trasformazioni geometriche e altri generici elementi di gioco;

Features opzionali implementate:

- IMPLEMENTATA: l'utente muove la racchetta a dx e sx;
- IMPLEMENTATA: il gioco � giocatile, movimento racchetta, pallina e collisioni pallina. I mattoncini si rompono al primo colpo, si ha una sola possibilit� poi il livello ricomincia.
- IMPLEMENTATA: Non tutti i mattoncini si rompono al primo colpo, alcuni al secondo colpo.
- IMPLEMENTATA: Quando si rompono alcuni mattoncini viene dato un bonus (non � necessario programmare l'effetto del bonus ma solo la grafica)

Features aggiuntive implementate:

- la pallina ha una texture, renderizzata tenendo conto del canale alpha nullo nelle zone non appartenenti al cerchio;
- ad ogni collisione con un muro o un mattoncino, la pallina aumenta o diminuisce la sua velocit� angolare,
	in base alla direzione in cui viene spinta;
- ad ogni collisione con la navicella, la velocit� angolare della pallina assume un valore direttamente proporzionale
	alla lontananza dal centro della navicella;
- ad ogni collisione con la navicella, la pallina viene deviata in maniera direttamente proporzionale
	alla lontananza dal centro della navicella;
- � un effetto voluto il fatto che ad ogni collisione con la navicella la pallina mantenga
	il verso della componente orizzontale della velocit� (nel gioco originale, colpendo la pallina
	con la parte sinistra della navicella la si manda verso sinistra, e viceversa);


Descrizione del funzionamento del gioco:

- nella classe GameManager � possibile settare le impostazioni dei vari componenti di gioco
	(grandezza della griglia, velocit� della pallina, ecc...);

- a gioco fermo, � possibile:
	premere il tasto N per cambiare la disposizione dei mattoncini;
	spostare a destra e a sinistra la navicella e la pallina
	(lo spostamento di quest'ultima fino ai limiti dello schermo � un effetto voluto, per dare pi� libert� al giocatore);

- la pressione della barra spaziatrice fa partire la pallina verso una direzione e ad una velocit� prefissate;

- descrizione dei mattoncini:
	sono presenti 7 tipi di mattoncini, 5 colorati e 2 con texture;
	alcuni si rompono in un colpo, altri in due;
	i mattoncini colorati una volta distrutti regalano un bonus (implementato solo come effetto grafico, con sistema particellare);

- distrutti tutti i mattoncini, la pallina si ferma. hai vinto!

- se la pallina collide con la parete inferiore hai perso, e il gioco viene resettato generando una nuova griglia e rimettendo
	navicella e pallina nelle posizioni iniziali.