// description
#type			j1939ss_getSPNnumber(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPNnumber;
}


bool			j1939ss_setSPNnumber(
	J1939SS_DATA	*this,
	#type			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPNnumber = value;

	return true;
}



// Requested Torque / Torque Limit
uint8_t			j1939ss_getSPN518(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN518;
}


bool			j1939ss_setSPN518(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN518 = value;

	return true;
}



// Override Control Mode
uint8_t			j1939ss_getSPN695(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN695;
}


bool			j1939ss_setSPN695(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN695 = value;

	return true;
}



// Requested Speed Control Conditions
uint8_t			j1939ss_getSPN696(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN696;
}


bool			j1939ss_setSPN696(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN696 = value;

	return true;
}



// Override Control Mode Priority
uint8_t			j1939ss_getSPN897(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN897;
}


bool			j1939ss_setSPN897(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN897 = value;

	return true;
}



// Requested Speed / Speed Limit
uint16_t			j1939ss_getSPN898(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN898;
}


bool			j1939ss_setSPN898(
	J1939SS_DATA	*this,
	uint16_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN898 = value;

	return true;
}



// Transmission Requested Range Display
uint8_t			j1939ss_getSPN1849(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN1849;
}


bool			j1939ss_setSPN1849(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN1849 = value;

	return true;
}



// Transmission Requested Range Display
uint8_t			j1939ss_getSPN1850(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN1850;
}


bool			j1939ss_setSPN1850(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN1850 = value;

	return true;
}



// Transmission Shift Inhibit Indicator
uint8_t			j1939ss_getSPN1851(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN1851;
}


bool			j1939ss_setSPN1851(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN1851 = value;

	return true;
}



// Transmission Mode 1 Indicator
uint8_t			j1939ss_getSPN2536(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN2536;
}


bool			j1939ss_setSPN2536(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN2536 = value;

	return true;
}



// Transmission Mode 2 Indicator
uint8_t			j1939ss_getSPN2537(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN2537;
}


bool			j1939ss_setSPN2537(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN2537 = value;

	return true;
}



// Transmission Mode 3 Indicator
uint8_t			j1939ss_getSPN2538(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN2538;
}


bool			j1939ss_setSPN2538(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN2538 = value;

	return true;
}



// Transmission Mode 4 Indicator
uint8_t			j1939ss_getSPN2539(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN2539;
}


bool			j1939ss_setSPN2539(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN2539 = value;

	return true;
}



// Transmission Engine Crank Enable
uint8_t			j1939ss_getSPN2900(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN2900;
}


bool			j1939ss_setSPN2900(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN2900 = value;

	return true;
}



// Active Shift Console Indicator
uint8_t			j1939ss_getSPN2945(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN2945;
}


bool			j1939ss_setSPN2945(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN2945 = value;

	return true;
}



// Transmission Ready for Brake Release
uint8_t			j1939ss_getSPN3086(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN3086;
}


bool			j1939ss_setSPN3086(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN3086 = value;

	return true;
}



// Transmission Requested Gear Feedback
uint8_t			j1939ss_getSPN3289(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN3289;
}


bool			j1939ss_setSPN3289(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN3289 = value;

	return true;
}



// TSC1 Transmission Rate
uint8_t			j1939ss_getSPN3349(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN3349;
}


bool			j1939ss_setSPN3349(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN3349 = value;

	return true;
}



// TSC1 Control Purpose
uint8_t			j1939ss_getSPN3350(
	J1939SS_DATA	*this
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
	return 0;
}
#endif

	return this->SPN3350;
}


bool			j1939ss_setSPN3350(
	J1939SS_DATA	*this,
	uint8_t			value
)
{

#ifdef NDEBUG
#else
	if (j1939ss_Validate(this)) {
	DEBUG_BREAK();
		return 0;
	}
#endif

	this->SPN3350 = value;

	return true;
}



