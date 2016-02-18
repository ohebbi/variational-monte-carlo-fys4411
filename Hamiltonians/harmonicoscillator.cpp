#include "harmonicoscillator.h"
#include <cmath>
#include <iostream>
#include "../system.h"
#include "../particle.h"
#include "../WaveFunctions/wavefunction.h"


using std::cout;
using std::endl;


HarmonicOscillator::HarmonicOscillator(System* system, double omega) :
        Hamiltonian(system) {
    m_omega  = omega;
    m_omega2 = omega*omega;
    m_exactGroundStateEnergyKnown = true;
    m_exactEnergy = (omega / 2.0) * system->getNumberOfDimensions() *
                                    system->getNumberOfParticles();
}

double HarmonicOscillator::computeLocalEnergy(Particle* particles) {
    double potentialEnergy = 0;
    for (int i=0; i < m_system->getNumberOfParticles(); i++) {
        double* position = particles[i].getPosition();
        double  r2       = 0;

        for (int j=0; j < m_system->getNumberOfDimensions(); j++) {
            r2 += position[j]*position[j];
        }
        potentialEnergy += 0.5 * m_omega2 * r2;
    }
    //double kineticEnergy = m_waveFunction->computeKineticEnergy(particles);
    double kineticEnergyNumerical = Hamiltonian::computeKineticEnergy(particles);
    return kineticEnergyNumerical + potentialEnergy;
}

