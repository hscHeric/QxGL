#include "extra.h"

bool glutGUI::iluminacao3D = true;  // AL

int glutGUI::width  = 400;
int glutGUI::height = 300;

bool  glutGUI::perspective  = true;
bool  glutGUI::pontosDeFuga = false;
bool  glutGUI::ortho        = true;
float glutGUI::orthof       = 0.0025;  // 0.003;

bool glutGUI::picking = false;

bool                                               glutGUI::lbpressed   = false;
bool                                               glutGUI::mbpressed   = false;
bool                                               glutGUI::rbpressed   = false;
bool                                               glutGUI::mouseMoving = false;
std::chrono::time_point<std::chrono::steady_clock> glutGUI::lastMoveTime =
  std::chrono::steady_clock::now();
const int glutGUI::IDLE_THRESHOLD_MS =
  100;  // tempo de inatividade do mouse para considerar que ele parou

MouseLock glutGUI::mouse_lock = NOT_LOCKED;
float     glutGUI::last_x     = 0.0;
float     glutGUI::last_y     = 0.0;

Camera *glutGUI::cam            = new CameraDistante();
float   glutGUI::savedCamera[9] = { 5, 5, 20, 0, 0, 0, 0, 1, 0 };

int   glutGUI::contRotation = 9999;
float glutGUI::value        = 90;
Axis  glutGUI::axis         = AXIS_Y;
int   glutGUI::nIterations  = 10;

int glutGUI::slices = 200;  // 400;//16;
int glutGUI::stacks = 200;  // 400;//16;

int glutGUI::posCam = 0;  // 1;

bool  glutGUI::iluminacao       = true;
bool  glutGUI::enabled_light[8] = { true, true, true, true, true, true, true, false };
bool  glutGUI::hidden_light[8]  = { false, false, false, false, false, false, false, false };
bool  glutGUI::pontual_light[8] = { true, true, true, true, true, true, true, true };
bool  glutGUI::spot_light[8]    = { false, false, false, false, false, false, false, false };
float glutGUI::spot_angle       = 25.0;
bool  glutGUI::trans_luz        = false;

bool  glutGUI::obj_transp    = false;
float glutGUI::transparencia = 0.5;

bool glutGUI::multiple_viewports = false;

bool glutGUI::draw_eixos = true;

bool glutGUI::trans_obj = false;

float glutGUI::tx = 0.0;
float glutGUI::ty = 0.0;
float glutGUI::tz = 0.0;

float glutGUI::ax = 0.0;
float glutGUI::ay = 0.0;
float glutGUI::az = 0.0;

float glutGUI::sx = 1.0;
float glutGUI::sy = 1.0;
float glutGUI::sz = 1.0;

float glutGUI::lx = 0.0;
float glutGUI::ly = 0.0;
float glutGUI::lz = 0.0;

float glutGUI::dtx = 0.0;
float glutGUI::dty = 0.0;
float glutGUI::dtz = 0.0;

float glutGUI::dax = 0.0;
float glutGUI::day = 0.0;
float glutGUI::daz = 0.0;

float glutGUI::dsx = 0.0;
float glutGUI::dsy = 0.0;
float glutGUI::dsz = 0.0;

float glutGUI::drx  = 0.0;
float glutGUI::dry  = 0.0;
float glutGUI::dlry = 0.0;

float glutGUI::dly  = 0.0;
float glutGUI::dlx  = 0.0;
float glutGUI::dlrx = 0.0;

float glutGUI::dmx  = 0.0;
float glutGUI::dmy  = 0.0;
float glutGUI::dlmy = 0.0;

// float glutGUI::delta = 5.0;

void glutGUI::resize( int w, int h ) {
  // glutGUI::width = w;
  // glutGUI::height = h;
  width  = w;
  height = h;
}

void glutGUI::defaultDisplay() {
  // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // cout << "Desenhando\n";
  // glutSwapBuffers();

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  const float ar = height > 0 ? (float)width / (float)height : 1.0;

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 30., ar, 0.1, 1000. );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  // viewport unica
  glViewport( 0, 0, width, height );
  glLoadIdentity();
  gluLookAt(
    cam->e.x, cam->e.y, cam->e.z, cam->c.x, cam->c.y, cam->c.z, cam->u.x, cam->u.y, cam->u.z );

  // LIGHT0
  // habilita luz
  glEnable( GL_LIGHT0 );
  // definindo intensidades de cor da luz
  GLfloat light_ambient[]  = { 0.2f, 0.2f, 0.2f, 1.0f };
  GLfloat light_diffuse[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
  GLfloat light_specular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
  glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
  glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );
  // posicionando a luz
  GLfloat light_position[] = { 0.0f, 1.0f, 0.0f, 1.0f };
  glLightfv( GL_LIGHT0, GL_POSITION, light_position );
  // desenha uma esfera representando a luz
  glDisable( GL_LIGHTING );
  glColor4f( 1.0, 1.0, 1.0, 1.0 );
  glPushMatrix();
  glTranslatef( light_position[0], light_position[1], light_position[2] );
  glutSolidSphere( 0.02, slices, stacks );
  glPopMatrix();
  glEnable( GL_LIGHTING );

  // desenha sistema de coordenadas global
  // glPushMatrix();
  // if (draw_eixos) Desenha::drawEixos(0.1);
  // glPopMatrix();

  // define cor
  GLfloat mat_ambient[]    = { 0.4, 0.2, 0.1, 1.0 };
  GLfloat mat_diffuse[]    = { 0.8, 0.4, 0.1, 1.0 };
  GLfloat mat_specular[]   = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat high_shininess[] = { 100.0f };

  glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
  glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
  glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
  glMaterialfv( GL_FRONT, GL_SHININESS, high_shininess );

  // desenha chao
  glDisable( GL_CULL_FACE );

  // int discr = 1;
  // Desenha::drawGrid( 5/discr, 0, 5/discr, discr );

  glPushMatrix();
  glTranslated( 0., -0.0001, 0. );
  float width       = 5.0;
  float height      = 5.0;
  float discrWidth  = 1;
  float discrHeight = 1;
  int   nWidth      = width / discrWidth;
  int   nHeight     = height / discrHeight;
  discrWidth =
    width / nWidth;  // correcao necessaria, pois, caso width/discrWidth nao seja inteiro,
                     // nWidth*discrWidth (feito pelo for) nao completara exatamente a width
  discrHeight =
    height / nHeight;  // correcao necessaria, pois, caso height/discrHeight nao seja inteiro,
                       // nHeight*discrHeight (feito pelo for) nao completara exatamente a height
  for ( float i = -0.5 * ( width / discrWidth ); i < 0.5 * ( width / discrWidth ); i++ ) {
    for ( float j = -0.5 * ( height / discrHeight ); j < 0.5 * ( height / discrHeight ); j++ ) {
      glPushMatrix();
      glTranslatef( i * discrWidth, 0.0, j * discrHeight );
      glBegin( GL_QUADS );
      glNormal3f( 0., 1., 0. );
      glVertex3f( 0.0, 0.0, +discrHeight );
      glVertex3f( +discrWidth, 0.0, +discrHeight );
      glVertex3f( +discrWidth, 0.0, 0.0 );
      glVertex3f( 0.0, 0.0, 0.0 );
      glEnd();
      glPopMatrix();
    }
  }
  glPopMatrix();

  glEnable( GL_CULL_FACE );

  glutSwapBuffers();
}

void glutGUI::changeCam() {
  posCam = ( posCam ) % 16;
  delete cam;
  switch ( posCam ) {
    case 0:
      glutGUI::perspective  = true;
      glutGUI::pontosDeFuga = false;
      cam                   = new CameraDistante();  // CameraDistante(0,1,10, 0,1,0, 0,1,0);
      break;
    case 1:
      glutGUI::perspective = false;
      glutGUI::ortho       = true;
      cam                  = new CameraDistante( 0, 1, 5, 0, 1, 0, 0, 1, 0 );
      break;
    case 2:
      glutGUI::perspective = false;
      glutGUI::ortho       = true;
      cam                  = new CameraDistante( 5, 1, 0, 0, 1, 0, 0, 1, 0 );
      // cam = new CameraDistante(5,0,0, 0,0,0, 0,1,-1);
      break;
    case 3:
      glutGUI::perspective = false;
      glutGUI::ortho       = true;
      cam                  = new CameraDistante( 0, 1, -5, 0, 1, 0, 0, 1, 0 );
      break;
    case 4:
      glutGUI::perspective = false;
      glutGUI::ortho       = true;
      cam                  = new CameraDistante( -5, 1, 0, 0, 1, 0, 0, 1, 0 );
      break;
    case 5:
      glutGUI::perspective = false;
      glutGUI::ortho       = true;
      cam                  = new CameraDistante( 0, 6, 0, 0, 1, 0, 0, 0, -1 );
      break;
    case 6:
      glutGUI::perspective = false;
      glutGUI::ortho       = true;
      cam                  = new CameraDistante( 0, -4, 0, 0, 1, 0, 0, 0, 1 );
      break;
    case 7:
      glutGUI::perspective = false;
      glutGUI::ortho       = true;
      cam                  = new CameraDistante( 7, 7, 7, 0, 0, 0, 0, 1, 0 );
      break;
    case 8:
      glutGUI::perspective = false;
      glutGUI::ortho       = true;
      cam                  = new CameraDistante( 6, 3, 6, 0, 0, 0, 0, 1, 0 );
      break;
    case 9:
      glutGUI::perspective = false;
      glutGUI::ortho       = true;
      cam                  = new CameraDistante( 6, 2, 4, 0, 0, 0, 0, 1, 0 );
      break;
    case 10:
      glutGUI::perspective = false;
      glutGUI::ortho       = false;
      cam                  = new CameraDistante( -2, 3, 5, -2, 3, 0, 0, 1, 0 );
      break;
    case 11:
      glutGUI::perspective  = true;
      glutGUI::pontosDeFuga = true;
      cam                   = new CameraDistante( 0, 1, 1.5, 0, 1, 0, 0, 1, 0 );
      break;
    case 12:
      glutGUI::perspective  = true;
      glutGUI::pontosDeFuga = true;
      cam                   = new CameraDistante( 1.2, 0.5, 1.2, 0, 0.5, 0, 0, 1, 0 );
      break;
    case 13:
      glutGUI::perspective  = true;
      glutGUI::pontosDeFuga = true;
      cam                   = new CameraDistante( 0.5, 1.2, 1.2, 0.5, 0.5, 0, 0, 1, 0 );
      break;
    case 14:
      glutGUI::perspective  = true;
      glutGUI::pontosDeFuga = true;
      cam                   = new CameraDistante( 1.2, 0.2, 1.2, 0, 1, 0, 0, 1, 0 );
      break;
    case 15:
      glutGUI::perspective  = true;
      glutGUI::pontosDeFuga = false;
      cam                   = new CameraDistante( savedCamera[0],
                                savedCamera[1],
                                savedCamera[2],
                                savedCamera[3],
                                savedCamera[4],
                                savedCamera[5],
                                savedCamera[6],
                                savedCamera[7],
                                savedCamera[8] );
      break;
  }
  orthof = 0.00025 * ( cam->c - cam->e ).modulo();
}

void glutGUI::defaultKey( unsigned char key, int x, int y ) {
  switch ( key ) {
    case 27:
    case 13:
    case 'q': exit( 0 ); break;

    case 'F': glutFullScreen(); break;
    case 'f': glutReshapeWindow( 800, 600 ); break;

    case 'o': glutGUI::perspective = !glutGUI::perspective; break;
    case 'O':
      glutGUI::ortho        = !glutGUI::ortho;
      glutGUI::pontosDeFuga = !glutGUI::pontosDeFuga;
      break;

    // case 'l':
    //     enabled_light[7] = !enabled_light[7];
    //     break;
    case '0' ... '7': enabled_light[key - '0'] = !enabled_light[key - '0']; break;

    case 'c':
      posCam--;
      posCam += 16;
      changeCam();
      break;
    case 'C':
      posCam++;
      changeCam();
      break;
    case 'j':
      posCam = 1;
      delete cam;
      cam = new CameraJogo();  // CameraDistante(0,1,5, 0,1,0, 0,1,0);
      break;
    case 's':
      // save current camera location
      savedCamera[0] = cam->e.x;
      savedCamera[1] = cam->e.y;
      savedCamera[2] = cam->e.z;
      savedCamera[3] = cam->c.x;
      savedCamera[4] = cam->c.y;
      savedCamera[5] = cam->c.z;
      savedCamera[6] = cam->u.x;
      savedCamera[7] = cam->u.y;
      savedCamera[8] = cam->u.z;
      break;

    case 'm': mouse_lock = MouseLock( ( int( mouse_lock ) + 1 ) % 3 ); break;

    case 'i':
      glutGUI::tx = 0.0;
      glutGUI::ty = 0.0;
      glutGUI::tz = 0.0;
      glutGUI::ax = 0.0;
      glutGUI::ay = 0.0;
      glutGUI::az = 0.0;
      glutGUI::sx = 1.0;
      glutGUI::sy = 1.0;
      glutGUI::sz = 1.0;
      glutGUI::lx = 0.0;
      glutGUI::ly = 0.0;
      glutGUI::lz = 0.0;
      break;

    case '=':
      glutGUI::slices += 5;
      glutGUI::stacks += 5;
      break;
    case '-':
      glutGUI::slices -= 5;
      glutGUI::stacks -= 5;
      break;

    case 'X': autoCamMove( -90, AXIS_X, nIterations ); break;
    case 'x': autoCamMove( 90, AXIS_X, nIterations ); break;
    case 'Y': autoCamMove( 90, AXIS_Y, nIterations ); break;
    case 'y': autoCamMove( -90, AXIS_Y, nIterations ); break;
    case 'Z': autoCamMove( 2, AXIS_Z, nIterations ); break;
    case 'z': autoCamMove( -2, AXIS_Z, nIterations ); break;
  }

  glutPostRedisplay();
}

void glutGUI::autoCamMove( float value, Axis axis, int nIterations ) {
  if ( axis == AXIS_Z && value < 0 && cam->e.getDistance( cam->c ) <= 1.001 )
    return;
  if ( axis == AXIS_Y && fabs( cam->u.y ) <= 0.1 )
    return;

  contRotation         = 0;
  glutGUI::value       = value;
  glutGUI::axis        = axis;
  glutGUI::nIterations = nIterations;
}

void glutGUI::autoCamMotion( float value, Axis axis, int nIterations ) {
  switch ( axis ) {
    case AXIS_X:
      if ( contRotation < nIterations ) {
        cam->rotatex( 0, ( HALF_PI / 90.0 ) * value / nIterations );
        contRotation++;
      }
      break;
    case AXIS_Y:
      if ( contRotation < nIterations ) {
        cam->rotatey( 0, ( HALF_PI / 90.0 ) * value / nIterations );
        contRotation++;
      }
      break;
    case AXIS_Z:
      if ( contRotation < nIterations ) {
        cam->zoom( 0, 20.0 * value / nIterations );
        contRotation++;
      }
      break;
  }
}

// detecta quando o mouse pára de mover,
// baseado no tempo após a última execução do mouseMove
void glutGUI::checkMouseIdle() {
  auto now = std::chrono::steady_clock::now();
  auto duration =
    std::chrono::duration_cast<std::chrono::milliseconds>( now - lastMoveTime ).count();

  if ( duration > IDLE_THRESHOLD_MS && mouseMoving ) {
    // std::cout << "Mouse parou de mover" << std::endl;
    mouseMoving = false;
  }
}

// os deltas do mouse precisam ser zerados periodicamente,
// pois eles estavam se mantendo com os valores calculados
// após a última execução do mouseMove
// zerar ao soltar o botão do mouse já ajuda, mas é normal acontecer
// de continuar segurando algum botão mesmo após parar de mover o mouse
//
// usar o idle no ubuntu foi suficiente, mas no windows os deltas ficavam sempre zerados, pois o
// idle é chamado muito mais frequentemente no windows do que no ubuntu
void glutGUI::idle() {
  checkMouseIdle();  // detecta quando o mouse pára de mover
  if ( !mouseMoving ) {
    dtx = 0.0;
    dty = 0.0;
    dtz = 0.0;
    dax = 0.0;
    day = 0.0;
    daz = 0.0;
    dsx = 0.0;
    dsy = 0.0;
    dsz = 0.0;

    drx  = 0.0;
    dry  = 0.0;
    dlry = 0.0;
    dly  = 0.0;
    dlx  = 0.0;
    dlrx = 0.0;
    dmx  = 0.0;
    dmy  = 0.0;
    dlmy = 0.0;
  }

  // autoCamMotion(value,axis,nIterations);
  glutPostRedisplay();
}

// timer foi criado para zerar os deltas em uma frequencia mais baixa,
// mas essa solução passa a depender da complexidade da cena
// na medida em que a cena demora mais a ser renderizada, o tempo de
// atualização precisa aumentar, senão os deltas voltam a ficar sempre zerados.
// o mais difícil foi perceber q os deltas pararam de funcionar por causa disso,
// o que torna essa solução com o timer muito ruim!
//
// a solução foi detectar quando o mouse parasse de mover (checkMouseIdle)
// timer não mais usado para zerar os deltas do mouse, apenas para o autoCamMotion
void glutGUI::timer( int time ) {
  // dtx = 0.0; dty = 0.0; dtz = 0.0;
  // dax = 0.0; day = 0.0; daz = 0.0;
  // dsx = 0.0; dsy = 0.0; dsz = 0.0;

  // drx = 0.0; dry = 0.0; dlry = 0.0;
  // dly = 0.0; dlx = 0.0; dlrx = 0.0;
  // dmx = 0.0; dmy = 0.0; dlmy = 0.0;

  autoCamMotion( value, axis, nIterations );
  glutPostRedisplay();

  glutTimerFunc(
    16, glutGUI::timer, 0 );  // Chama a função novamente após 16 milissegundos (~60 FPS)
  // glutTimerFunc(64, glutGUI::timer, 0);  // Chama a função novamente após 64 milissegundos
  // passei a chamar no próprio mouseMove, mas também não funcionou como desejado
}

void glutGUI::defaultMouseButton( int button, int state, int x, int y ) {
  dtx = 0.0;
  dty = 0.0;
  dtz = 0.0;
  dax = 0.0;
  day = 0.0;
  daz = 0.0;
  dsx = 0.0;
  dsy = 0.0;
  dsz = 0.0;

  drx  = 0.0;
  dry  = 0.0;
  dlry = 0.0;
  dly  = 0.0;
  dlx  = 0.0;
  dlrx = 0.0;
  dmx  = 0.0;
  dmy  = 0.0;
  dlmy = 0.0;

  // if the left button is pressed
  if ( button == GLUT_LEFT_BUTTON ) {
    // when the button is pressed
    if ( state == GLUT_DOWN ) {
      lbpressed = true;
      //            //picking
      //            int pick = picking( x, y, 5, 5 );
      //            if (pick == 0)
      //              lbpressed = true;
      //            else
      //              objeto_selecionado = pick;
    } else {  // state = GLUT_UP
      lbpressed = false;
    }
  }
  // if the middle button is pressed
  if ( button == GLUT_MIDDLE_BUTTON ) {
    // when the button is pressed
    if ( state == GLUT_DOWN ) {
      mbpressed = true;
    } else {  // state = GLUT_UP
      mbpressed = false;
    }
  }
  // if the left button is pressed
  if ( button == GLUT_RIGHT_BUTTON ) {
    // when the button is pressed
    if ( state == GLUT_DOWN ) {
      rbpressed = true;
      // picking
      //             objeto_selecionado = 0;
    } else {  // state = GLUT_UP
      rbpressed = false;
    }
  }

  last_x = x;
  last_y = y;
}

// botao direito         bt dir e esq
// horiz      vert       vert
// dtx = 0.0; dty = 0.0; dtz = 0.0;

// botao esq             bt dir e esq
// vert       horiz      horiz
// dax = 0.0; day = 0.0; daz = 0.0;

// botao meio            bt esq e meio
// horiz      vert       vert
// dsx = 0.0; dsy = 0.0; dsz = 0.0;

void glutGUI::mouseMove( int x, int y ) {
  if ( mouse_lock == ONLY_X )
    last_y = y;
  if ( mouse_lock == ONLY_Y )
    last_x = x;

  lastMoveTime = std::chrono::steady_clock::now();
  mouseMoving  = true;

  dtx = 0.0;
  dty = 0.0;
  dtz = 0.0;
  dax = 0.0;
  day = 0.0;
  daz = 0.0;
  dsx = 0.0;
  dsy = 0.0;
  dsz = 0.0;

  drx  = 0.0;
  dry  = 0.0;
  dlry = 0.0;
  dly  = 0.0;
  dlx  = 0.0;
  dlrx = 0.0;
  dmx  = 0.0;
  dmy  = 0.0;
  dlmy = 0.0;

  float fator = 10.0;
  if ( lbpressed && !rbpressed && !mbpressed ) {
    if ( !trans_obj && ( !trans_luz || !obj_transp ) ) {
      cam->rotatex( y, last_y );
      cam->rotatey( x, last_x );
    }
    if ( trans_obj ) {
      dly = dax = ( y - last_y ) / fator;
      dlx = day = ( x - last_x ) / fator;
      ax += dax;
      ay += day;
    }
    if ( trans_luz && obj_transp ) {
      fator = 100.0;
      transparencia -= ( y - last_y ) / fator;
      if ( transparencia < 0.0 )
        transparencia = 0.0;
      if ( transparencia > 1.0 )
        transparencia = 1.0;
    }
  }
  fator = 100.0;
  if ( !lbpressed && rbpressed && !mbpressed ) {
    if ( !trans_obj && !trans_luz ) {
      cam->translatex( x, last_x );
      cam->translatey( y, last_y );
    }
    if ( trans_obj ) {
      drx = dtx = ( x - last_x ) / fator;
      dry = dty = -( y - last_y ) / fator;
      tx += dtx;
      ty += dty;
    }
    if ( trans_luz ) {
      lx += ( x - last_x ) / fator;
      ly += -( y - last_y ) / fator;
    }
  }
  if ( lbpressed && rbpressed && !mbpressed ) {
    if ( !trans_obj && !trans_luz ) {
      cam->zoom( y, last_y );
      // orthof += -(y - last_y)/50000.0;
      orthof = 0.00025 * ( cam->c - cam->e ).modulo();
      // cam->rotatez(x,last_x);
    }
    if ( trans_obj ) {
      fator = 100.0;
      dlry = dtz = ( y - last_y ) / fator;
      tz += dtz;
      fator = 10.0;
      dlrx = daz = -( x - last_x ) / fator;
      az += daz;
    }
    if ( trans_luz ) {
      fator = 100.0;
      lz += ( y - last_y ) / fator;
      fator = 10.0;
      spot_angle += -( x - last_x ) / fator;
    }
  }
  fator = 100.0;
  if ( !lbpressed && !rbpressed && mbpressed ) {
    if ( !trans_obj ) {
    } else {
      dmx = dsx = ( x - last_x ) / fator;
      dmy = dsy = -( y - last_y ) / fator;
      sx += dsx;
      sy += dsy;
    }
  }
  if ( lbpressed && !rbpressed && mbpressed ) {
    if ( !trans_obj ) {
    } else {
      dlmy = dsz = ( y - last_y ) / fator;
      sz += dsz;
    }
  }

  last_x = x;
  last_y = y;
}

//------------------------------------------------

void glutGUI::multGLMatrixByVector( float res[4], float matriz[16], float entr[4] ) {
  for ( int i = 0; i < 4; i++ ) {
    res[i] = 0.0;
    for ( int j = 0; j < 4; j++ ) {
      // res[i] += matriz[4*i+j] * entr[j];
      res[i] += matriz[4 * j + i] * entr[j];  // matriz^T.entr
    }
  }
}

void glutGUI::showGLMatrixIn2D( float matriz[16] ) {
  for ( int i = 0; i < 4; i++ ) {
    for ( int j = 0; j < 4; j++ ) {
      // cout << matriz[4*i+j] << "  ";
      // cout << matriz[4*j+i] << "  "; //matriz^T
      cout << setiosflags( ios::fixed ) << setprecision( 2 ) << matriz[4 * j + i]
           << "  ";  // matriz^T
    }
    cout << "\n";
  }
  // cout << "\n";
}

void glutGUI::composite() {
  // 3D
  // glTranslated(tx,ty,tz);
  // glRotated(az,0,0,1);
  // glRotated(ay,0,1,0);
  // glRotated(ax,1,0,0);
  // glScaled(sx,sy,sz);
  // 2D
  glTranslated( tx, ty, 0.0 );
  glRotated( az, 0, 0, 1 );
  glScaled( sx, sy, 1.0 );
}

void glutGUI::showLocalAndGlobalCoords( float pl[4] ) {
  // imprimindo coords locais e coords globais
  // locais
  cout << "Coords locais: " << pl[0] << ", " << pl[1] << ", " << pl[2] << "\n";
  // globais
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glLoadIdentity();
  // composicao de transformacoes
  composite();
  // obtendo e mostrando a matriz de composicao (matriz modelView atual) no console
  float compositeMatrix[16];
  glGetFloatv( GL_MODELVIEW_MATRIX, compositeMatrix );
  showGLMatrixIn2D( compositeMatrix );
  // ponto em coords globais é obtido pelo ponto em coords locais transformado pela matriz de
  // composicao
  float pg[4];
  multGLMatrixByVector( pg, compositeMatrix, pl );
  cout << "Coords globais: " << pg[0] << ", " << pg[1] << ", " << pg[2] << "\n\n";
  glPopMatrix();
}

Vetor3D glutGUI::transformedPoint( Vetor3D p, transformFunction transformGL ) {
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glLoadIdentity();

  // glRotatef(objetos[0]->a.z,0,0,1);  // \ .
  // glRotatef(objetos[0]->a.y,0,1,0);  //  | Rz.Ry.Rx . v
  // glRotatef(objetos[0]->a.x,1,0,0);
  transformGL();

  float matrix[16];
  glGetFloatv( GL_MODELVIEW_MATRIX, matrix );
  glPopMatrix();

  float pos[4] = { p.x, p.y, p.z, 1.0 };
  float res[4];

  glutGUI::multGLMatrixByVector( res, matrix, pos );

  Vetor3D res3D = Vetor3D( res[0], res[1], res[2] );
  return res3D;
}
