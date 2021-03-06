/* Maxime Brodat
 * maxime.brodat@utbm.fr
 *
 * Stéphane Perrez
 * stephane.perrez@utbm.fr
 *
 * Deadline: 01/05/2015
 */

/* ----- INCLUDE ----- */

#include <stdio.h>
#include <stdlib.h>

/* ----- HEADERS ----- */

#include "polygon.h"

/* ----- FUNCTIONS ----- */

/* Creates a 2D-Point according to the specified abscissa and ordinate
 * newX - double, abscissa coordinate
 * newY - double, ordinate coordinate
 * newPoint - newly created point
 */
Point createPoint (double newX, double newY)
{
    Point newPoint;
    newPoint.x = newX;
    newPoint.y = newY;
    return newPoint;
}

/* Creates an empty polygon
 * newPolygon - Polygon, newly created empty polygon
 */
Polygon createPolygon ()
{
    Polygon newPolygon;
    newPolygon.head = NULL;
    newPolygon.size = 0;
    return newPolygon;
}

/* Empties a polygon's data
 * polygon - Polygon, specified polygon to empty
 */
Polygon emptyPolygon(Polygon polygon)
{
    if(polygon.size != 0)
    {
        Element* p = polygon.head->prev->prev; /* p - temporary pointer on an Element */

        while(p->index > 1) /* deletes all elements until the first one is reached */
        {
            free(p->next);
            p = p->prev;
        }

        /* when you reach the first one */
        if(polygon.size != 1) /* delete the second one if it does exist */
        {
            free(p->next);
        }

        free(p); /* delete the first one */
        polygon.head = NULL; /* reset the polygon's informations */
        polygon.size = 0;
    }

    return polygon;
}

/* Adds the specified point to the specified polygon
 * polygon - Polygon, specified polygon to which we want to add a point
 * point - Point, specified point we want to add to the polygon
 */
Polygon addPoint (Point point, Polygon polygon)
{
    Element* newElem = (Element*)malloc(sizeof(Element)); /* memory allocation for the new element */
    newElem->value = point;
    newElem->index = polygon.size + 1; /* the new element will be putted at the end of the list */

    if(polygon.size == 0) /* if the polygon is empty */
    {
        newElem->prev = newElem; /* the next and prev pointers of newElem are set */
        newElem->next = newElem;
        polygon.head = newElem; /* the head of the polygon is set */
    }

    else /* if the polygon contains at least one element */
    {
        newElem->prev = polygon.head->prev; /* the next and prev pointers of newElement are set */
        newElem->next = polygon.head;
        newElem->prev->next = newElem; /* the next and prev pointers of the new neighbours of newElem are set */
        newElem->next->prev = newElem;
    }

    polygon.size++; /* polygon's size is increased */
    return polygon;
}

/* Removes a specified point from the specified polygon
 * polygon - Polygon, specified polygon on which we want to remove a point
 * i - integer, rank of the point from the head of the list of points
 */
Polygon removePoint (Polygon polygon, int i)
{
    if(i > 0 && i <= polygon.size) /* if the chosen point does exist */
    {
        int k = 1;
        Element* p = polygon.head; /* pointer on the first element of the list */
        Element* n = polygon.head->prev; /* pointer on the last element of the list */
        if(i==1 && polygon.size != 1)
        {
            polygon.head = p->next; /* the head of the list is changed iff the first element is targeted */
        }

        while(k<i)
        {
            k++;
            p = p->next; /* temporary pointer is moved until the targeted point is reached */
        }

        if(polygon.size != 1)
        {
            p->next->prev = p->prev; /* links between the elements around the targeted element changed */
            p->prev->next = p->next;
            free(p);

            for(k=polygon.size;k>i;k--)
            {
                n->index--; /* index of the next elements after the removed one are decreased */
                n = n->prev;
            }
        }

        else
        {
            polygon.head = NULL; /* if no element left, polygon turned into an empty one */
            free(p);
        }

        polygon.size--; /* polygon size is decreased */
    }
    return polygon;
}




/* Displays the coordinates of the specified point
 * point - Point, specified point to display
 */
void printPoint (Point point)
{
    printf("[%.2f,%.2f]",point.x, point.y);
}

/* Displays the coordinates of all the points of a specified polygon
 * polygon - Polygon, specified polygon to display
 */
void printPolygon (Polygon polygon)
{
    Element* p = polygon.head;
    printf("[");

    if(polygon.size != 0)
    {
        do
        {
            if(p->index != 1)
            {
                printf(",");
            }

            printPoint(p->value);
            p = p->next;
        } while(p != polygon.head);
    }

    printf("]");
}
