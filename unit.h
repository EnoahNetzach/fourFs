/*
 * unit.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_UNIT_H_
#define fourFs_UNIT_H_

namespace FourFs
{

class State;

class Unit
{
public:
   explicit Unit(State & linkedState);
   ~Unit();

   const unsigned & longevity() const;
   const unsigned & fertility() const;
   const unsigned & belligerance() const;
   const State & linkedState() const;

protected:

private:
   static unsigned m_area;
   static unsigned m_fieldOfView;
   double m_longevity;
   double m_fertility;
   double m_belligerance;
   // TODO m_linkedPixels [&]
   // TODO m_linkedState [&]
   State * m_linkedState;

};

} /* namespace FourFs */

#endif /* fourFs_UNIT_H_ */
