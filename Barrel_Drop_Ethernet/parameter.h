#ifndef _PARAMETER_H_
#define _PARAMETER_H_

class ParameterBase
{
public:

    ParameterBase(bool use_eeprom, size_t size) : m_use_eeprom(use_eeprom), m_changed(false), m_setup_done(false)
    {
        if (m_use_eeprom)
        {
            m_eeprom_location.size = size;
        }
    }
    
    void setup()
    {
        if (!m_use_eeprom)
        {
            this->reset();
            adl_logln(LOG_ADL, "Reset");
        }
        else
        {
            adl_nv_alloc(m_eeprom_location);
            this->load();    
            adl_logln(LOG_ADL, "Load");
        }
        m_setup_done = true;
    }

    bool has_changed()
    {
        bool changed = m_changed;
        m_changed = false;
        return changed;
    }

    virtual void reset() = 0;
    virtual int command_handler(char const * const command, char * reply) = 0;
    virtual void save() = 0;
    virtual void load() = 0;
    
protected:
    bool m_use_eeprom;
    bool m_changed = false;
    bool m_setup_done = false;

    ADL_NV_LOCATION m_eeprom_location;

    void on_change()
    {
        if (m_use_eeprom && m_setup_done)
        {
            this->save();
        }
        m_changed = true;
    }
};

#ifdef UNITTEST
class TestParam : public ParameterBase
{
public:
    TestParam();
    void reset() {};
    void setup() {};
    int command_handler(char const * const command, char * reply);

    void save() { adl_nv_save(&m_data, m_eeprom_location); }
    void load() { adl_nv_load(&m_data, m_eeprom_location); }

    int32_t m_data;
    char m_last_command[128];
};
#endif

#endif
