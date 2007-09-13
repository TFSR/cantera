/**
 *  @file Nasa9Poly1.h
 *  Header for a single-species standard state object derived
 *  from 
 *  \link Cantera::SpeciesThermoInterpType SpeciesThermoInterpType\endlink  based 
 *  on the NASA 9 coefficient temperature polynomial form applied to
 *   one temperature region
 *  (see \ref spthermo and class \link Cantera::Nasa9Poly1 Nasa9Poly1\endlink).
 *
 *  This parameterization has one NASA temperature region.
 */


#ifndef CT_NASA9POLY1_H
#define CT_NASA9POLY1_H


/* $Author$
 * $Revision$
 * $Date$
 */

// Copyright 2007  Sandia National Laboratories


#include "global.h"
#include "SpeciesThermoInterpType.h"

namespace Cantera {

 
  //! The NASA 9 polynomial parameterization for one temperature range.
  /*!
   * This parameterization expresses the heat capacity via a
   * 7 coefficient polynomial.
   * 
   *  Note that this is the form used in the
   * 2002 NASA equilibrium program
   *
   *  NASA Glenn Coefficients for Calculating Thermodynamic
   *  Properties of Individual Species, 
   *  B. J. McBride, M. J. Zehe, S. Gordon
   *  NASA/TP-2002-211556, Sept. 2002
   *
   *
   * Nine coefficients \f$(a_0,\dots,a_6)\f$ are used to represent
   * \f$ C_p^0(T)\f$, \f$ H^0(T)\f$, and \f$ S^0(T) \f$ as 
   * polynomials in \f$ T \f$ :  
   * \f[
   * \frac{c_p(T)}{R} = a_0 T^{-2} + a_1 T^{-1} + a_2 + a_3 T 
   *                  + a_4 T^2 + a_5 T^3 + a_6 T^4
   * \f]
   * 
   * \f[
   * \frac{H^0(T)}{RT} = - a_0 T^{-2} + a_1 \frac{\ln(T)}{T} + a_2 
   * + a_3 T + a_4 T^2  + a_5 T^3 + a_6 T^4 + \frac{a_7}{T}
   * \f]
   *
   * \f[
   * \frac{s^0(T)}{R} = - \frac{a_0}{2} T^{-2} - a_1 T^{-1} + a_2 \ln(T)
   +    + a_3 T  \frac{a_4}{2} T^2 + \frac{a_5}{3} T^3  + \frac{a_6}{4} T^4 + a_8 
   * \f]
   * 
   *  The standard state is assumed to be the ideal gas at the
   *  standard pressure of 1 bar, for gases.
   *  For condensed species, the standard state is the
   *  pure cyrstalline or liquid substance at the standard
   *  pressure of 1 atm.
   * 
   * These NASA representations may have more than 2 temperature regions.
   *
   * @ingroup spthermo
   */
  class Nasa9Poly1 : public SpeciesThermoInterpType {

  public:

    //! Empty constructor
    Nasa9Poly1();


    //! constructor used in templated instantiations
    /*!
     * @param n            Species index
     * @param tlow         Minimum temperature
     * @param thigh        Maximum temperature
     * @param pref         reference pressure (Pa).
     * @param coeffs       Vector of coefficients used to set the
     *                     parameters for the standard state.
     */
    Nasa9Poly1(int n, doublereal tlow, doublereal thigh, doublereal pref,
	       const doublereal* coeffs);

    //! copy constructor
    /*!
     * @param b object to be copied
     */
    Nasa9Poly1(const Nasa9Poly1& b);

    //! assignment operator
    /*!
     * @param b object to be copied
     */
    Nasa9Poly1& operator=(const Nasa9Poly1& b);

    //! Destructor
    virtual ~Nasa9Poly1();

    //! duplicator
    virtual SpeciesThermoInterpType *
    duplMyselfAsSpeciesThermoInterpType() const;

    //! Returns the minimum temperature that the thermo
    //! parameterization is valid
    virtual doublereal minTemp() const;

    //! Returns the maximum temperature that the thermo
    //! parameterization is valid
    virtual doublereal maxTemp() const;

    //! Returns the reference pressure (Pa)
    virtual doublereal refPressure() const;

    //! Returns an integer representing the type of parameterization
    virtual int reportType() const;

    //! Returns an integer representing the species index
    virtual int speciesIndex() const;

    //! Update the properties for this species, given a temperature polynomial
    /*!
     * This method is called with a pointer to an array containing the functions of
     * temperature needed by this  parameterization, and three pointers to arrays where the
     * computed property values should be written. This method updates only one value in
     * each array.
     *
     * Temperature Polynomial:
     *  tt[0] = t;
     *  tt[1] = t*t;
     *  tt[2] = t*t*t;
     *  tt[3] = t*t*t*t;
     *  tt[4] = 1.0/t;
     *  tt[5] = 1.0/(t*t);
     *  tt[6] = std::log(t);
     *
     * @param tt      vector of temperature polynomials
     * @param cp_R    Vector of Dimensionless heat capacities.
     *                (length m_kk).
     * @param h_RT    Vector of Dimensionless enthalpies.
     *                (length m_kk).
     * @param s_R     Vector of Dimensionless entropies.
     *                (length m_kk).
     */
    virtual void updateProperties(const doublereal* tt, 
				  doublereal* cp_R, doublereal* h_RT, doublereal* s_R) const;

 
    //! Compute the reference-state property of one species
    /*!
     * Given temperature T in K, this method updates the values of
     * the non-dimensional heat capacity at constant pressure,
     * enthalpy, and entropy, at the reference pressure, Pref
     * of one of the species. The species index is used
     * to reference into the cp_R, h_RT, and s_R arrays.
     *
     * Temperature Polynomial:
     *  tt[0] = t;
     *  tt[1] = t*t;
     *  tt[2] = t*t*t;
     *  tt[3] = t*t*t*t;
     *  tt[4] = 1.0/t;
     *  tt[5] = 1.0/(t*t);
     *  tt[6] = std::log(t);
     *
     * @param temp    Temperature (Kelvin)
     * @param cp_R    Vector of Dimensionless heat capacities.
     *                (length m_kk).
     * @param h_RT    Vector of Dimensionless enthalpies.
     *                (length m_kk).
     * @param s_R     Vector of Dimensionless entropies.
     *                (length m_kk).
     */
    virtual void updatePropertiesTemp(const doublereal temp, 
				      doublereal* cp_R, doublereal* h_RT, 
				      doublereal* s_R) const;

    //!This utility function reports back the type of 
    //! parameterization and all of the parameters for the 
    //! species, index.
    /*!
     * All parameters are output variables
     *
     * @param n         Species index
     * @param type      Integer type of the standard type
     * @param tlow      output - Minimum temperature
     * @param thigh     output - Maximum temperature
     * @param pref      output - reference pressure (Pa).
     * @param coeffs    Vector of coefficients used to set the
     *                  parameters for the standard state.
     */
    virtual void reportParameters(int &n, int &type,
				  doublereal &tlow, doublereal &thigh,
				  doublereal &pref,
				  doublereal* const coeffs) const;

    //! Modify parameters for the standard state
    /*!
     * @param coeffs   Vector of coefficients used to set the
     *                 parameters for the standard state.
     */
    virtual void modifyParameters(doublereal* coeffs);

  protected:
    //! lowest valid temperature
    doublereal m_lowT;    
    //! highest valid temperature
    doublereal m_highT;   
    //! standard-state pressure
    doublereal m_Pref;     
    //! species index
    int m_index;  
    //! array of polynomial coefficients       
    array_fp m_coeff;
  };

}
#endif

