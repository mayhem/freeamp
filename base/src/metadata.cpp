#include "metadata.h"
// Under the GPL
// Chris Kuklewicz
// chrisk@mit.edu

HashStore * MetaData::m_store=NULL;
ostream& MetaData::print_stream(ostream& out)
{
    out << "m_artist   (" << m_artist    << ")" << endl;
    out << "m_album    (" << m_album     << ")" << endl;
    out << "m_title    (" << m_title     << ")" << endl;
    out << "m_genre    (" << m_genre     << ")" << endl;
    out << "m_comment  (" << m_comment   << ")" << endl;
    out << "m_extension(" << m_extension << ")" << endl;
    out << "m_guid     (" << m_guid      << ")" << endl;
    out << "m_year     = " << m_year      << endl;
    out << "m_track    = " << m_track     << endl;
    out << "m_time     = " << m_time      << endl;
    out << "m_size     = " << m_size      << endl;
    out << "m_playcount= " << m_playcount << endl;
    return out;
}


ostream& operator<< (ostream& out, MetaData& metadata)
{
    return metadata.print_stream(out);
}
