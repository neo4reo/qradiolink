// Written by Adrian Musceac YO8RZZ , started March 2016.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include "gr_mod_ssb_sdr.h"

gr_mod_ssb_sdr_sptr make_gr_mod_ssb_sdr(int sps, int samp_rate, int carrier_freq,
                                          int filter_width)
{
    return gnuradio::get_initial_sptr(new gr_mod_ssb_sdr(sps, samp_rate, carrier_freq,
                                                      filter_width));
}

gr_mod_ssb_sdr::gr_mod_ssb_sdr(int sps, int samp_rate, int carrier_freq,
                                 int filter_width) :
    gr::hier_block2 ("gr_mod_ssb_sdr",
                      gr::io_signature::make (1, 1, sizeof (float)),
                      gr::io_signature::make (1, 1, sizeof (gr_complex)))
{


    _samp_rate =samp_rate;
    float target_samp_rate = 8000.0;
    _carrier_freq = carrier_freq;
    _filter_width = filter_width;

    _agc = gr::analog::agc2_ff::make(1000, 1000, 1, 0);
    _audio_filter = gr::filter::fft_filter_fff::make(
                1,gr::filter::firdes::low_pass(
                    1, target_samp_rate, _filter_width, 600, gr::filter::firdes::WIN_BLACKMAN_HARRIS));
    _float_to_complex = gr::blocks::float_to_complex::make();
    std::vector<float> interp_taps = gr::filter::firdes::low_pass(1, _samp_rate,
                                                        _filter_width, 1200);

    _resampler = gr::filter::rational_resampler_base_ccf::make(125,4, interp_taps);
    _amplify = gr::blocks::multiply_const_cc::make(0.2,1);
    _filter_usb = gr::filter::fft_filter_ccc::make(
                1,gr::filter::firdes::complex_band_pass_2(
                    1, _samp_rate, 300, _filter_width, 50, 120, gr::filter::firdes::WIN_BLACKMAN_HARRIS));
    _filter_lsb = gr::filter::fft_filter_ccc::make(
                1,gr::filter::firdes::complex_band_pass_2(
                    1, _samp_rate, -_filter_width, -300, 50, 120, gr::filter::firdes::WIN_BLACKMAN_HARRIS));



    connect(self(),0,_agc,0);
    connect(_agc,0,_float_to_complex,0);
    connect(_float_to_complex,0,_resampler,0);
    connect(_resampler,0,_amplify,0);
    if(!sps)
    {
        connect(_amplify,0,_filter_usb,0);
        connect(_filter_usb,0,self(),0);
    }
    else
    {
        connect(_amplify,0,_filter_lsb,0);
        connect(_filter_lsb,0,self(),0);
    }
}

