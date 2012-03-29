/*!
  \file   main.cpp
  \author  Team Exception
  \date   Wed Mar 28 18:36:38 2012
  
  \brief  WidgetTown, fun for everyone!
  A CS3505 project for playing with Qt
  
*/

#include "Constants.h"
#include "characterview.h"
#include "customproxy.h"
#include "npc.h"
#include "player.h"
#include "tilescene.h"

#include <QtGui/QApplication>
#include <QCalendarWidget>
#include <QLabel>
#include <QTimer>
#include <QtGui>

#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[])
{
  srand((unsigned)time(0)); // Get some fresh random numbers up in here

  QApplication a(argc, argv);

  // Set up a scene with our map
  TileScene scene(":/tileset.png", ":/map.tmx");

  // Add the player
  Player player(":/nerd.png");
  scene.addCharacter(&player);
  player.setFocus();
  player.setPos(14 * TILE_WIDTH, 20 * TILE_HEIGHT);

  // Set up a view of our scene
  CharacterView view(&scene);
  view.character = &player;
  view.scale(2, 2); // Make it big and pixelly
  view.setRenderHints(view.renderHints() | QPainter::Antialiasing | QPainter::SmoothPixmapTransform); // Smooth and shiny pixelly
  view.resize(800, 600); // A good game size
  scene.setFocus(); // The scene gets input events

  // We need some friends
  NPC chris(":/nerd.png");
  scene.addCharacter(&chris);
  chris.setPos(14 * TILE_WIDTH, 30 * TILE_HEIGHT);

  NPC joe(":/nerd.png");
  scene.addCharacter(&joe);
  joe.setPos(15 * TILE_WIDTH, 30 * TILE_HEIGHT);

  NPC jim(":/nerd.png");
  scene.addCharacter(&jim);
  jim.setPos(12 * TILE_WIDTH, 30 * TILE_HEIGHT);

  NPC matt(":/nerd.png");
  scene.addCharacter(&matt);
  matt.setPos(14 * TILE_WIDTH, 35 * TILE_HEIGHT);

  // Set up frame timer
  QTimer *frameTimer = new QTimer();
  // Update the view and the scene on ticks
  view.connect(frameTimer, SIGNAL(timeout()), &view, SLOT(tick()));
  scene.connect(frameTimer, SIGNAL(timeout()), &scene, SLOT(tick()));
  frameTimer->start(1000 / 30); // 30 FPS

  //------LABEL WIDGET------
  CustomProxy *desk = new CustomProxy(0, Qt::Window);
  desk->setWidget(new QLabel("I'm a Banana!"));
  desk->setScale(.10);
  desk->setPos(TILE_WIDTH / 2 +(9 * TILE_WIDTH), TILE_HEIGHT / 2 + (7 * TILE_HEIGHT));
  desk->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
  desk->setZValue(LAYER_COUNT);
  scene.addItem(desk);

  //------CALENDAR WIDGET------
  CustomProxy *proxy = new CustomProxy(0, Qt::Window);
  proxy->setWidget(new QCalendarWidget);
  proxy->setScale(.10);
  proxy->setPos(TILE_WIDTH / 2 +(16 * TILE_WIDTH), TILE_HEIGHT / 2 + (4 * TILE_HEIGHT));
  proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
  proxy->setZValue(LAYER_COUNT);
  scene.addItem(proxy);

  // Add a second game in the first
  TileScene scene2(":/tileset.png", ":/map.tmx");
  CharacterView view2(&scene2, 2);
  view2.resize(300,300);
  Player player2(":/nerd.png");
  scene2.addCharacter(&player2);
  view2.character = &player2;
  player2.setFocus();
  player2.setPos(14 * TILE_WIDTH, 20 * TILE_HEIGHT);
  CustomProxy *thegame = new CustomProxy(0, Qt::Window);
  thegame->setWidget(&view2);
  thegame->setScale(.20);
  thegame->setPos(TILE_WIDTH / 2 +(25 * TILE_WIDTH), TILE_HEIGHT / 2 + (25 * TILE_HEIGHT));
  thegame->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
  thegame->setZValue(LAYER_COUNT);
  scene.addItem(thegame);
  view2.centerOn(&player2);
  view2.connect(frameTimer, SIGNAL(timeout()), &view2, SLOT(tick()));
  scene2.connect(frameTimer, SIGNAL(timeout()), &scene2, SLOT(tick()));

  // Add a third game in the second
  TileScene scene3(":/tileset.png", ":/map.tmx");
  CharacterView view3(&scene3, 3);
  view3.resize(300,300);
  Player player3(":/nerd.png");
  scene3.addCharacter(&player3);
  view3.character = &player3;
  player3.setFocus();
  player3.setPos(14 * TILE_WIDTH, 20 * TILE_HEIGHT);
  CustomProxy *thegame2 = new CustomProxy(0, Qt::Window);
  thegame2->setWidget(&view3);
  thegame2->setScale(.20);
  thegame2->setPos(TILE_WIDTH / 2 +(25 * TILE_WIDTH), TILE_HEIGHT / 2 + (25 * TILE_HEIGHT));
  thegame2->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
  thegame2->setZValue(LAYER_COUNT);
  scene2.addItem(thegame2);
  view3.centerOn(&player3);
  view3.connect(frameTimer, SIGNAL(timeout()), &view3, SLOT(tick()));
  scene3.connect(frameTimer, SIGNAL(timeout()), &scene3, SLOT(tick()));

  view.centerOn(&player); // Lookin' at the player
  view.show();
  return a.exec(); // Here we go!
}
