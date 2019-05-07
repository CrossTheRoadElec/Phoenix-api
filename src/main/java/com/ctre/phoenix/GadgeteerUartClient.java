package com.ctre.phoenix;

/**
 * Interface for uart gadgeteer devices
 */
public interface GadgeteerUartClient
{
	/**
	 * Device connected to gadgeteer
	 */
	public enum GadgeteerProxyType{
		/**
		 * General Gadgeteer Proxy
		 */
		General(0), 
		/**
		 * Pigeon connected to gadgeteer
		 */
		Pigeon(1), 
		/**
		 * HERO connected to gadgeteer
		 */
		PC_HERO(2),
		/**
		 * Device unknown
		 */
		Unknown(-1);

		private int value; 
		private GadgeteerProxyType(int value) { this.value = value; }
		
		/**
		 * Get GadgeteerProxyType of specified value
		 * @param value Value of GadgeteerProxyType
		 * @return GadgeteerProxyType of specified value
		 */
		public static GadgeteerProxyType valueOf(int value) {
			for (GadgeteerProxyType e : GadgeteerProxyType.values()) {
				if (e.value == value) {
					return e;
				}
			}
			return Unknown;
		}
	};

	/**
	 * Method of connection to gadgeteer
	 */
	public enum GadgeteerConnection	{
		/**
		 * Device not connected
		 */
		NotConnected (0),
		/**
		 * Device in process of connecting
		 */
		Connecting (1),
		/**
		 * Device is connected
		 */
		Connected (2),
		/**
		 * Device unknown
		 */
		Unknown(-1);
		
		private int value; 
		private GadgeteerConnection(int value) { this.value = value; } 

		/**
		 * Get GadgeteerConnection of specified value
		 * @param value Value of GadgeteerConnection
		 * @return GadgeteerConnection of specified value
		 */
		public static GadgeteerConnection valueOf(int value) {
			for (GadgeteerConnection e : GadgeteerConnection.values()) {
				if (e.value == value) {
					return e;
				}
			}
			return Unknown;
		}
	};

	/**
	 * The status of the gadgeteer device
	 */
	public static class GadgeteerUartStatus {
		/** Type of gadgeteer */
		public GadgeteerProxyType type;
		/** Connection status */
		public GadgeteerConnection conn;
		/** Bitrate of connection */
		public int bitrate;
		/** Number of resets that have happened */
		public int resetCount;
	};

	/**
	 * Gets gadgeteer status
	 * @param status status object to fill
	 * @return ErrorCode
	 */
    int getGadgeteerStatus(GadgeteerUartStatus status);
};

