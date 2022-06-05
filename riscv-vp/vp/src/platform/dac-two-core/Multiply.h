#ifndef MULTIPLY_H_
#define MULTIPLY_H_
#include <cmath>
#include <iomanip>
#include <systemc>
using namespace sc_core;

#include <tlm_utils/simple_target_socket.h>

#include <tlm>

#include "dac_def.h"

struct MULTIPLY : public sc_module {
	tlm_utils::simple_target_socket<MULTIPLY> tsock;

	sc_fifo<unsigned int> a_0;
	sc_fifo<unsigned int> a_1;
	sc_fifo<unsigned int> a_2;
	sc_fifo<unsigned int> a_3;
	sc_fifo<unsigned int> b_0;
	sc_fifo<unsigned int> b_1;
	sc_fifo<unsigned int> b_2;
	sc_fifo<unsigned int> b_3;
	sc_fifo<unsigned int> c_0;
	sc_fifo<unsigned int> c_1;
	sc_fifo<unsigned int> c_2;
	sc_fifo<unsigned int> c_3;

	SC_HAS_PROCESS(MULTIPLY);

	MULTIPLY(sc_module_name n) : sc_module(n), tsock("t_skt"), base_offset(0) {
		tsock.register_b_transport(this, &MULTIPLY::blocking_transport);
		SC_THREAD(do_multiply);
	}

	~MULTIPLY() {}

	unsigned int base_offset;

	void do_multiply() {
		{ wait(CLOCK_PERIOD, SC_NS); }
		while (true) {
			int a0 = 0; int a1 = 0; int a2 = 0; int a3 = 0;
			int b0 = 0; int b1 = 0; int b2 = 0; int b3 = 0;
			int c0 = 0; int c1 = 0; int c2 = 0; int c3 = 0;

			a0 = a_0.read();
			a1 = a_1.read();
			a2 = a_2.read();
			a3 = a_3.read();
			b0 = b_0.read();
			b1 = b_1.read();
			b2 = b_2.read();
			b3 = b_3.read();
			c0 = a0 * b0 + a1 * b2;
			c1 = a0 * b1 + a1 * b3;
			c2 = a2 * b0 + a3 * b2;
			c3 = a2 * b1 + a3 * b3;
			wait(CLOCK_PERIOD, SC_NS);

			c_0.write(c0);
			c_1.write(c1);
			c_2.write(c2);
			c_3.write(c3);
			wait(CLOCK_PERIOD, SC_NS);
		}
	}

	void blocking_transport(tlm::tlm_generic_payload &payload, sc_core::sc_time &delay) {
		wait(delay);
		// unsigned char *mask_ptr = payload.get_byte_enable_ptr();
		// auto len = payload.get_data_length();
		tlm::tlm_command cmd = payload.get_command();
		sc_dt::uint64 addr = payload.get_address();
		unsigned char *data_ptr = payload.get_data_ptr();

		addr -= base_offset;

		// cout << (int)data_ptr[0] << endl;
		// cout << (int)data_ptr[1] << endl;
		// cout << (int)data_ptr[2] << endl;
		// word buffer;
		switch (cmd) {
			case tlm::TLM_READ_COMMAND:
				// cout << "READ" << endl;
				switch (addr) {
					case MULTIPLY_RESULT_ADDR_0:
						data_ptr[0] = c_0.read(); break;
					case MULTIPLY_RESULT_ADDR_1:
						data_ptr[0] = c_1.read(); break;
					case MULTIPLY_RESULT_ADDR_2:
						data_ptr[0] = c_2.read(); break;
					case MULTIPLY_RESULT_ADDR_3:
						data_ptr[0] = c_3.read(); break;
					default:
						std::cerr << "READ Error! MULTIPLY::blocking_transport: address 0x"
						          << std::setfill('0') << std::setw(8) << std::hex << addr << std::dec
						          << " is not valid" << std::endl;
				}
				break;
			case tlm::TLM_WRITE_COMMAND:
				// cout << "WRITE" << endl;
				switch (addr) {
					case MULTIPLY_R_ADDR_0:
						a_0.write(data_ptr[0]); break;
					case MULTIPLY_R_ADDR_1:
						a_1.write(data_ptr[0]); break;
					case MULTIPLY_R_ADDR_2:
						a_2.write(data_ptr[0]); break;
					case MULTIPLY_R_ADDR_3:
						a_3.write(data_ptr[0]); break;
					case MULTIPLY_R_ADDR_4:
						b_0.write(data_ptr[0]); break;
					case MULTIPLY_R_ADDR_5:
						b_1.write(data_ptr[0]); break;
					case MULTIPLY_R_ADDR_6:
						b_2.write(data_ptr[0]); break;
					case MULTIPLY_R_ADDR_7:
						b_3.write(data_ptr[0]); break;
					default:
						std::cerr << "WRITE Error! MULTIPLY::blocking_transport: address 0x"
						          << std::setfill('0') << std::setw(8) << std::hex << addr << std::dec
						          << " is not valid" << std::endl;
				}
				break;
			case tlm::TLM_IGNORE_COMMAND:
				payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
				return;
			default:
				payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
				return;
		}
		payload.set_response_status(tlm::TLM_OK_RESPONSE);  // Always OK
	}
};
#endif
