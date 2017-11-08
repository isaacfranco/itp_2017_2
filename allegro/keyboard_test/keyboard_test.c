#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

int main(int argc, char * argv[]) {
	ALLEGRO_DISPLAY *tela;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *fila_eventos;
	float fps = 60.0;
	float frame_time = 1.0 / fps;
	int sair = 0;

	/* inicializar allegro */
	al_init();

	/* inicializar addons utilizados */
	al_init_primitives_addon();

	al_install_keyboard();

	/* criar recursos */
	tela = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	fila_eventos = al_create_event_queue();
	timer = al_create_timer(frame_time);


	/* registrar event_sources na fila_eventos */
	al_register_event_source( fila_eventos, al_get_display_event_source(tela) );
	al_register_event_source( fila_eventos, al_get_timer_event_source(timer) );
	al_register_event_source( fila_eventos, al_get_keyboard_event_source() );

	/* iniciar o timer para gerar eventos para a fila */
	al_start_timer(timer);

	while ( !sair ) {
		ALLEGRO_EVENT evento_atual;

		/* aguardar evento qualquer e salvar ele em "evento_atual" */
		al_wait_for_event(fila_eventos, &evento_atual);

		switch (evento_atual.type) {
			case ALLEGRO_EVENT_TIMER:
				/* timer ocorreu (1 por frame) */
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				/* clicar em fechar janela */
				sair = 1;
				break;
			default:
				printf("Evento desconhecido encontrado tipo: %i\n", evento_atual.type);
				break;
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(tela);

}