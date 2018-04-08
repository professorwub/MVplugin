// Reverb effect based on generalized state space filter
// Updated 4/7/2018
// Warren L. G. Koontz

#define ORDER 8 // number of waveguide pairs
#define ULTDELAY 24000 // maximum waveguide delay in samples
#define GOLD 0.0011f // factor to convert sq ft to sample delay based on golden rectangle

class Mverb
{
public:

	Mverb();
	~Mverb();

	//Parameters
	float pctRev; // "percent" reverb (range 0 - 1)
	float level; // level converted from dB

	// Methods
	void Update(float, float, float, float); // Called to adjust waveguide parameters
	void Process(float*, float*, int); // Process block of stereo samples

	private:

	// delay lines
	float east [ORDER][ULTDELAY];
	float west [ORDER][ULTDELAY];
	int head;
	int tail[ORDER];
	float damp [ORDER];
	float gain [ORDER];
	
	// state vectors
	float xEast [ORDER];
	float xWest [ORDER];
};