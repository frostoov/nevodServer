import asyncio
import json
import time  # TODO


class EasClient:

    def __init__(self):
        self.control_client = _Client()
        self.data_client = _Client()
        self.queue = []
        self.id = 0

    def set_callback_functions(self, control_callback, data_callback):
        self.control_callback = control_callback
        self.control_client.set_callback(self.callback_for_control_client)
        self.data_client.set_callback(data_callback)

    def connect_client_to_server(self, ip, control_port, data_port):
        self.control_client.connect_to(ip, control_port)
        self.data_client.connect_to(ip, data_port)

    def connect_server_to_host(self, host_number,
                               host_ip, control_port, data_port):
        host_ip = "192.168.2.40"    # TODO
        rpc_json = self.__get_rpc_json("eas_connectToHost",
                                       [host_number, host_ip,
                                        control_port, data_port])
        self.queue.append(rpc_json)

    def disconnect_client_from_server(self):
        self.control_client.disconnect_from()
        self.data_client.disconnect_from()

    def disconnect_server_from_host(self, id_host):
        rpc_json = self.__get_rpc_json("eas_disconnectFromHost", [id_host])
        self.queue.append(rpc_json)

    def add_master_to_host(self, id_master):
        rpc_json = self.__get_rpc_json("eas_addMasterToHost", [id_master])
        self.queue.append(rpc_json)

    def add_adc_to_master(self, id_adc):
        rpc_json = self.__get_rpc_json("eas_addAdcToMaster", [id_adc])
        self.queue.append(rpc_json)

    def set_settings_configuration(self, name_of_configuration):
        rpc_json = self.__get_rpc_json("eas_setDefaultSettings",
                                       [name_of_configuration])
        self.queue.append(rpc_json)

    def set_threshold(self, id_paa, channel, threshold):
        rpc_json = self.__get_rpc_json("eas_writeThreshold",
                                       [id_paa, channel, threshold])
        self.queue.append(rpc_json)

    def set_thresholds_to_all(self, threshold):
        rpc_json = self.__get_rpc_json("eas_writeThresholdsToAll",
                                       [id_paa, threshold])
        self.queue.append(rpc_json)

    def set_coincidence(self, id_master, coincidence):
        rpc_json = self.__get_rpc_json("eas_writeThreshold",
                                       [id_master, coincidence])
        self.queue.append(rpc_json)

    def set_coincidence_to_all(self, coincidence):
        rpc_json = self.__get_rpc_json("eas_writeSetCoincidenceAll",
                                       [coincidence])
        self.queue.append(rpc_json)

    def hard_reset(self, id_master):
        rpc_json = self.__get_rpc_json("eas_writeHardReset", [id_master])
        self.queue.append(rpc_json)

    def reset_vme(self, id_master):
        rpc_json = self.__get_rpc_json("eas_writeResetVme", [id_master])
        self.queue.append(rpc_json)

    def start_work(self, id_paa, threshold):
        # TODO
        rpc_json = self.__get_rpc_json("eas_writeThreshold",
                                       [id_paa, threshold])
        self.queue.append(rpc_json)

    def allow_work_with_master(self, id_master, is_work=None):
        if is_work is None:
            is_work = True
        rpc_json = self.__get_rpc_json("eas_writePermissionOfMasters",
                                       [id_master, is_work])
        self.queue.append(rpc_json)

    def allow_work_with_host(self, id_host, is_on_first, is_on_second,
                             is_on_third, is_on_fourth):
        rpc_json = self.__get_rpc_json("eas_writeRegisterOfReadData",
                                       [id_host, is_on_first, is_on_second,
                                        is_on_third, is_on_fourth])
        self.queue.append(rpc_json)

    def allow_work_with_masters(self, id_host, is_on_first, is_on_second,
                                is_on_third, is_on_fourth):
        rpc_json = self.__get_rpc_json("eas_writePermissionOfData",
                                       [id_host, is_on_first, is_on_second,
                                        is_on_third, is_on_fourth])
        self.queue.append(rpc_json)

    def reset_adc(self, id_adc):
        rpc_json = self.__get_rpc_json("eas_writeControlRegister",
                                       [id_adc])
        self.queue.append(rpc_json)

    def set_time_gate(self, id_master, nanoseconds):
        rpc_json = self.__get_rpc_json("eas_writeSetTimeGate",
                                       [id_master, nanoseconds])
        self.queue.append(rpc_json)

    def set_time_gate_to_all(self, nanoseconds):
        rpc_json = self.__get_rpc_json("eas_writeSetTimeGateToAll",
                                       [nanoseconds])
        self.queue.append(rpc_json)

    def set_task_table(self, id_master):
        rpc_json = self.__get_rpc_json("eas_setTaskTable", [id_master])
        self.queue.append(rpc_json)

    def set_task_table_to_all(self):
        rpc_json = self.__get_rpc_json("eas_writeTaskTable", [])
        self.queue.append(rpc_json)

    def set_active_channels_to_master(self, id_master, is_on_first,
                                      is_on_second, is_on_third,
                                      is_on_fourth, is_on_fifth,
                                      is_on_sixth, is_on_seventh,
                                      is_on_eighth):
        rpc_json = self.__get_rpc_json("eas_writeActiveChannels",
                                       [id_master, is_on_first,
                                        is_on_second, is_on_third,
                                        is_on_fourth, is_on_fifth,
                                        is_on_sixth, is_on_seventh,
                                        is_on_eighth])
        self.queue.append(rpc_json)

    def reset_adc_channel(self, id_paa, channel):
        rpc_json = self.__get_rpc_json("eas_writeResetChannel",
                                       [id_paa, channel])
        self.queue.append(rpc_json)

    def write200200(self, id_master):
        rpc_json = self.__get_rpc_json("eas_write200200",
                                       [id_master])
        self.queue.append(rpc_json)

    def resolution_and_forbid_of_data(self, id_host, resolution):
        rpc_json = self.__get_rpc_json("eas_resolutionAndFordbidOfData",
                                       [id_host, resolution])
        self.queue.append(rpc_json)

    def control_dma(self, id_host, is_on):
        rpc_json = self.__get_rpc_json("eas_writeControlDma",
                                       [id_host, is_on])
        self.queue.append(rpc_json)

    def resolution_data_zero(self, id_host):
        rpc_json = self.__get_rpc_json("eas_resolutionDataZero", [id_host])
        self.queue.append(rpc_json)

    def send_queue_to(self):
        for command in self.queue:
            self.control_client.send_to(command)
            time.sleep(1)
        self.queue.clear()
        self.id = 0

    def callback_for_control_client(self, msg):
        try:
            answer_json = json.loads(msg)
            answer_queue = []
            id_list = [item["id"] for item in self.queue]
            if isinstance(answer_json, list):
                for command in answer_json:
                    if command["id"] in id_list:
                        answer_queue.append(
                         (self.queue[id_list.index(command["id"])]["method"],
                          command["result"])
                        )
                        del self.queue[id_list.index(command["id"])]
            else:
                if answer_json["id"] in id_list:
                    answer_queue.append(
                     (self.queue[id_list.index(answer_json["id"])]["method"],
                      answer_json["result"])
                    )
                    del self.queue[id_list.index(answer_json["id"])]

            self.control_callback(answer_queue)
        except():
            print("Invalid Json")

    def __get_rpc_json(self, name_of_method, list_of_arguments):
        rpc_json = {
            "jsonrpc": "2.0",
            "method": name_of_method,
            "params": list_of_arguments,
            "id": self.id
        }
        self.id += 1
        return rpc_json


class _Client:

    def __init__(self):
        pass

    def connect_to(self, ip, port):
        asyncio.ensure_future(self.__connect_to(ip, port))

    def send_to(self, msg):
        self.writer.write((str(msg) + "\n").encode("utf-8"))

    def disconnect_from(self):
        self.reader.close()
        self.writer.close()

    def set_callback(self, callback):
        self.callback = callback

    @asyncio.coroutine
    def __connect_to(self, ip, port):
        self.reader, self.writer = yield from asyncio.open_connection(ip, port)
        future = asyncio.Future()
        asyncio.ensure_future(self.__receive_from(future))
        future.add_done_callback(self.__receive_from_callback)

    @asyncio.coroutine
    def __send_to(self, msg):
        self.writer.write((msg + "\n").encode("utf-8"))

    @asyncio.coroutine
    def __receive_from(self, future):
        line = yield from self.reader.readline()
        future.set_result(line.decode("utf-8"))

    def __receive_from_callback(self, future):
        self.callback(future.result())

        future = asyncio.Future()
        asyncio.ensure_future(self.__receive_from(future))
        future.add_done_callback(self.__receive_from_callback)
