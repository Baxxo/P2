
Sala [NomeSala, NumPosti, Posti(Array as matrix)]

Tracking=>container di Biglietti (storico di persone entrate in sala per tracking)

Storico=>container dei biglietti e abbonamenti venduti

Utente[Nome, Cognome, CF, recapito, congiunti(array di CF di utenti)]

Famiglia[Codice, Componenti(array di utente)]
	
EntrataFilm [utente, data, prezzo]

	Biglietto[Riduzione, Film, data->dataOraAcquisto, posto]

	Abbonamento[Codice, Entrate, FasciaOraria]->

		Singolo[]-> metodo polimorfo Prezzo(..)
			GetPrezzo()=>return Prezzo*MoltiplicatoreFasceOrarie	

		Famiglia[NumeroMembri]-> metodo polimorfo Prezzo(..)
			FetPrezzo=>return prezzo*Numeromembri


// Ha senso la specializzazione singolo/famiglia per identificare univocamente con il dinamic cast (regole posti diverse in singolo/famiglia)			

Regole[Distanziamento, mascherina bool]

	Bianca->tutti amici sempre

	Gialla->distanziati di un posto, però congiunti vicini

	Arancione->distanti di x posti, però congiunti vicini + mascherina

	Rossa->tutti distanti + mascherina

	
	