#include <gl/glut.h>
#include <math.h>
#include <time.h>

const GLfloat tam_x = 50.0f;
const GLfloat tam_y = 50.0f;

const GLint sy = 30;
const GLint my = 25;
const GLint hy = 20;

int hora;
int minuto;
int segundo;

void circulo(GLfloat xc, GLfloat yc, GLfloat raio, bool fill)
{
  const GLfloat c = 3.14169f / 180.0f;
  GLint i;
  
  glBegin(fill ? GL_TRIANGLE_FAN : GL_LINE_LOOP);
  
  for (i = 0; i <= 360; i += 2)
  {
    float a = i * c;
    glVertex2f(xc + sin(a) * raio, yc + cos(a) * raio);
  }
  
  glEnd();
}

// Função callback chamada para fazer o desenho
void desenha(void)
{
	//Limpa a janela de visualização com a cor de fundo especificada 
	glClear(GL_COLOR_BUFFER_BIT);

    // Desenha os circulos	
    glColor3f(1.0f, 1.0f, 0.0f); // amarelo
    circulo(0, 0, tam_x, true);
    
    glColor3f(0.0f, 0.0f, 0.0f); // preto
    circulo(0, 0, tam_x, false);  
    
    // Calcula o angulo do segundo
    float anguloS = segundo * 6;
    
    // Desenha o ponteiro do segundo
    glRotatef(-anguloS, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // vermelho
    glVertex2i(0,0);
    glVertex2i(0,sy);
    glEnd();
    
    glLoadIdentity(); // Limpa as transformacoes

    // Calcula o angulo do minuto
    float anguloM = minuto * 6;

    // Desenha o ponteiro do minuto
    glRotatef(-anguloM, 0.0f, 0.0f, 1.0f);

	glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2i(0,0);
    glVertex2i(0,my);
    glEnd();
    
    glLoadIdentity(); // Limpa as transformacoes

    // Calcula o angulo da hora
	float anguloH = (hora + minuto/60.0) * 30;

    // Desenha o ponteiro da hora
    glRotatef(-anguloH, 0.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2i(0,0);
    glVertex2i(0,hy);
    glEnd();
    
    glLoadIdentity(); // Limpa as transformacoes

	//Executa os comandos OpenGL 
	glFlush();
}

void redimensiona(GLsizei largura, GLsizei altura)
{
     // Redimensiona a viewport para ficar com o mesmo tamanho da janela
     glViewport(0, 0, largura, altura);    
   
    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Faz o mapeamento entre a viewport e o sistema de coordenadas 2D
    // levando em consideracao a relacao entre a largura e a altura da viewport
    // Nesse caso, o objeto renderizado vai mudar de tamanho conforme a janela
    // aumentar ou diminuir
    if (largura <= altura)
       gluOrtho2D(-tam_x, tam_x, -tam_y * altura / largura, tam_y * altura / largura);
    else
       gluOrtho2D(-tam_x * largura / altura, tam_x * largura / altura, -tam_y, tam_y);
       
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void move(int n)
{
     // Apos a execucao desse trecho a estrutura "datahora"
     // tera armazenada a data/hora atual do relogio da maquina
     time_t agora = time(0);
     struct tm *datahora = localtime(&agora);
     
     hora = datahora->tm_hour;
     minuto = datahora->tm_min;
     segundo = datahora->tm_sec;
     
     glutPostRedisplay(); // Pede para redesenhar a tela. Vai chamar a funcao desenha()
     glutTimerFunc(1000, move, 0);     // Pede para chamar de novo a funcao move
}

// Inicializa parâmetros de rendering
void inicializa (void)
{   
    // Define a cor de fundo da janela de visualização (RGB)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400,400);
    glutInitWindowPosition(10,10);
	glutCreateWindow("Relogio");
	glutDisplayFunc(desenha);
	glutReshapeFunc(redimensiona);
	glutTimerFunc(1000, move, 0);
	inicializa();
	glutMainLoop();
	return 0;
}
