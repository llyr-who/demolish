#include<iostream>
#include"scenario.h"
#include"glut.h"
#include"render.h"
#include"matrix.h"

using namespace demolish;

world::Scenario scenario(0.1,10);

void displayfunc(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scenario.render();
    
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2f(1,1);
    glVertex2f(11,1);
    glEnd();

    displayString( 0.2, 0.1, "WASD to move" );
    if(scenario.breachedSpheres())
    {
        displayString(0.2,0.3,"Sphere Breached");
    }
    if(scenario.breachedHulls())
    {
        displayString(0.2,0.5,"Convex Hull Breached");
    }
    if(scenario.hasCollision())
    {
        displayString(3,0.1,"Collision!!!!!!!!!!!!!!!!!!!");
    }
    auto cpsvec = scenario.obtainCollisionPoints();
    for(auto&cps:cpsvec)
    { 
        glColor3f(1,0.5,0.5);
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glVertex2f(cps.getX(),cps.getY());
        glEnd();
    }
    cpsvec = scenario.obtainCHCollisionPoints();
    for(auto&cps:cpsvec)
    { 
        glColor3f(0,1,0);
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glVertex2f(cps.getX(),cps.getY());
        glEnd();
    }
    auto cpsvecofpairs = scenario.obtainEdgesUnderConsideration();
    for(auto&cps:cpsvecofpairs)
    { 
        glColor3f(0,1,0);
        glPointSize(5.0);
        glBegin(GL_LINES);
        glVertex2f(cps.first.getX(),cps.first.getY());
        glVertex2f(cps.second.getX(),cps.second.getY());
        glEnd();
    }
    glutSwapBuffers();
}

// we are going to use this function to move one of the 
// objects and make it "collide" with the other object.
//

void physics(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    
    scenario.step();

    glutPostRedisplay();
  
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key)
  {
  case 's':
    scenario.manuallyMoveObject(0,0,-0.1);
    glutPostRedisplay();
    break;
  case 'w':
    scenario.manuallyMoveObject(0,0,0.1);
    glutPostRedisplay();
    break;
  case 'd':
    scenario.manuallyMoveObject(0,0.1,0);
    glutPostRedisplay();
    break;
  case 'a':
    scenario.manuallyMoveObject(0,-0.1,0);
    glutPostRedisplay();
    break;
  }
}


int main(int argc, char** argv)
{
    std::vector<Vertex> verts1;

    /*
     *  "K"
     */

    
    verts1.push_back(Vertex(1,1));
    verts1.push_back(Vertex(0.5,1.9));
    verts1.push_back(Vertex(0,0.7));
    verts1.push_back(Vertex(-0.5,0.9));
    verts1.push_back(Vertex(-1,1));
    verts1.push_back(Vertex(-0.5,0));
    verts1.push_back(Vertex(-1,-1));
    verts1.push_back(Vertex(0,-0.7));
    verts1.push_back(Vertex(1,-1));
    verts1.push_back(Vertex(1.3,0.05));


    std::vector<Vertex> verts2;

    /*
     *  "Kv2"
     */

    
    verts2.push_back(Vertex(1,1));
    verts2.push_back(Vertex(0,0.7));
    verts2.push_back(Vertex(-0.5,1.1));
    verts2.push_back(Vertex(-1,1));
    verts2.push_back(Vertex(-0.5,0));
    verts2.push_back(Vertex(-1,-1));
    verts2.push_back(Vertex(0,-0.9));
    verts2.push_back(Vertex(1,-1));
    verts2.push_back(Vertex(0.5,0.05));
    verts2.push_back(Vertex(0.7,-0.1));
     
    std::vector<Vertex> verts3;

    /*
     *  "somethinelse"
     */

    verts3.push_back(Vertex( 0  ,3));    
    verts3.push_back(Vertex(-1  ,1));
    verts3.push_back(Vertex(-0.8,0.8 ));
    verts3.push_back(Vertex(-1  ,0.6));
    verts3.push_back(Vertex(-0.8,0.4 ));
    verts3.push_back(Vertex(-1  ,0.2));
    verts3.push_back(Vertex(-0.8,0 ));
    verts3.push_back(Vertex(1  ,0));
    verts3.push_back(Vertex(0.8,0.1 ));
    verts3.push_back(Vertex(1  ,0.5));
    verts3.push_back(Vertex(0.8,0.7 ));
    verts3.push_back(Vertex(1  ,0.9));
    verts3.push_back(Vertex(0.8,1 ));
    std::array<float,2> locObj1 = {5,5};
    std::array<float,2> locObj2 = {3,8};
    std::array<float,2> locObj3 = {8,3};

    auto poly1= geometry::Polygon(verts1);
    auto poly2= geometry::Polygon(verts2);
    auto poly3= geometry::Polygon(verts3);

    auto obj1 = world::Object(poly1,locObj1);
    auto obj2 = world::Object(poly2,locObj2);
    auto obj3 = world::Object(poly3,locObj3);

    scenario.addObjectToScenario(obj1);
    scenario.addObjectToScenario(obj2);
    scenario.addObjectToScenario(obj3);

    obj1.displayProperties();

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutInitWindowSize( 1024, 768 );
    glutCreateWindow( "demolish 1.0" );
    glutDisplayFunc(displayfunc);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(physics);

    glMatrixMode( GL_PROJECTION );
    glPushMatrix( );
    glLoadIdentity( );
    gluOrtho2D( 0, 12, 0, 10 );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );
    glLoadIdentity( );


    glutMainLoop( );

    return 0;
}
