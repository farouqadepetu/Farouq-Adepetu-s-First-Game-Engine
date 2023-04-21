#pragma once

/** @file FABuffer.h
*	@brief File has classes RenderTargetBuffer, DepthStencilBuffer, StaticBuffer and DynamicBuffer under namespace FARender.
*/

#include <wrl.h>
#include <d3d12.h>

/** @namespace FARender
*	@brief Has classes that are used for rendering objects and text through the Direct3D 12 API.
*/
namespace FARender
{
	/** @class RenderTargetBuffer ""
	*	@brief A wrapper for render target buffer resources. Uses DirectD 12 API.
	*/
	class RenderTargetBuffer
	{
	public:
		/**@brief Default Constructor.
		* 
		* @param[in] format The format of the render target buffer.
		*/
		RenderTargetBuffer(DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);

		/**@brief Returns the format of the render target buffer.
		*/
		DXGI_FORMAT GetRenderTargetFormat() const;

		/**@brief Returns a reference to the render target buffer.
		*/
		Microsoft::WRL::ComPtr<ID3D12Resource>& GetRenderTargetBuffer();

		/**@brief Returns a constant reference to the render target buffer.
		*/
		const Microsoft::WRL::ComPtr<ID3D12Resource>& GetRenderTargetBuffer() const;

		/**@brief Creates the render target buffer and view.
		* 
		* @param[in] device A Direct3D 12 device.
		* @param[in] rtvHeap A descriptor heap for storing render target descriptors.
		* @param[in] indexOfWhereToStoreView The index of where to store the created descriptor in the descriptor heap.
		* @param[in] rtvSize The size of a render target descriptor.
		* @param[in] width The width of the render target buffer.
		* @param[in] height The height of the render target buffer.
		* @param[in] sampleCount The sample count of the render target buffer.
		*/
		void CreateRenderTargetBufferAndView(const Microsoft::WRL::ComPtr<ID3D12Device>& device,
			const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& rtvHeap, unsigned int indexOfWhereToStoreView, unsigned int rtvSize,
			unsigned int width, unsigned int height, unsigned int sampleCount = 1);

		/**@brief Resets the render target buffer.
		*/
		void ResetBuffer();

		/**@brief Clears the render target buffer with the specified clear value.
		* 
		* @param[in] commadList A Direct3D 12 graphics command list.
		* @param[in] rtvHeap A render target descriptor heap.
		* @param[in] indexOfView The index of where the render target descriptor of the 
		* render target buffer is stored in the descriptor heap.
		* 
		* @param[in] rtvSize The size of a render target descriptor.
		* @param[in] clearValue The RGBA values of what to set every element in the render target buffer to.
		*/
		void ClearRenderTargetBuffer(const Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& commandList,
			const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& rtvHeap, unsigned int indexOfView, unsigned int rtvSize,
			const float* clearValue);

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> mRenderTargetBuffer;
		DXGI_FORMAT mRenderTargetFormat;

	};

	/** @class DepthStencilBuffer ""
	*	@brief A wrapper for depth stencil buffer resources. Uses DirectD 12 API.
	*/
	class DepthStencilBuffer
	{
	public:

		/**@brief Default Constructor.
		* 
		* @param[in] format The format of the depth stencil buffer.
		*/
		DepthStencilBuffer(DXGI_FORMAT format = DXGI_FORMAT_D24_UNORM_S8_UINT);

		/**@brief Returns the format of the depth stencil buffer.
		*/
		DXGI_FORMAT GetDepthStencilFormat() const;

		/**@brief Creates the depth stencil buffer and view.
		* 
		* @param[in] device A Direct3D 12 device.
		* @param[in] dsvHeap A descriptor heap for storing depth stencil descriptors.
		* @param[in] indexOfWhereToStoreView The index of where to store the created descriptor in the descriptor heap.
		* @param[in] dsvSize The size of a depth stenicl descriptor.
		* @param[in] width The width of the depth stenicl buffer.
		* @param[in] height The height of the depth stenicl buffer.
		* @param[in] sampleCount The sample count of the depth stenicl buffer.
		*/
		void CreateDepthStencilBufferAndView(const Microsoft::WRL::ComPtr<ID3D12Device>& device,
			const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& dsvHeap, unsigned int indexOfWhereToStoreView, unsigned int dsvSize,
			unsigned int width, unsigned int height, unsigned int sampleCount = 1);

		/**@brief Resets the depth stencil buffer.
		*/
		void ResetBuffer();

		/**@brief Clears the depth stencil buffer with the specified clear value.
		* 
		* @param[in] commadList A Direct3D 12 graphics command list.
		* @param[in] dsvHeap A depth stencil descriptor heap.
		* @param[in] indexOfView The index of where the depth stencil descriptor of the  
		* depth stencil buffer is stored in the descriptor heap.
		* 
		* @param[in] dsvSize The size of a depth stencil descriptor.
		* @param[in] clearValue The value of what to set every element in the depth stencil buffer to.
		*/
		void ClearDepthStencilBuffer(const Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& commandList,
			const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& dsvHeap, unsigned int indexOfView, unsigned int dsvSize,
			float clearValue);

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer;
		DXGI_FORMAT mDepthStencilFormat;
	};


	/** @class StaticBuffer ""
	*	@brief This class stores data in a Direct3D 12 default buffer.
	*/
	class StaticBuffer
	{
	public:
		StaticBuffer() = default;
		StaticBuffer(const StaticBuffer&) = delete;
		StaticBuffer& operator=(const StaticBuffer&) = delete;

		StaticBuffer(StaticBuffer&&) = default;

		/**@brief Creates the static buffer and stores all of the specified data.
		* 
		* @param[in] device A Direct3D 12 device.
		* @param[in] commadList A Direct3D 12 graphics command list.
		* @param[in] data The data to store in the static buffer.
		* @param[in] numBytes The number of bytes to store in the static buffer.
		*/
		void CreateStaticBuffer(const Microsoft::WRL::ComPtr<ID3D12Device>& device,
			const Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>& commandList, const void* data, UINT numBytes);

		/**@brief Creates a vertex buffer view and stores it.
		* 
		* @param[in] numBytes The number of bytes in the static buffer.
		* @param[in] stride The number of bytes to get from one element to another in the static buffer.
		*/
		void CreateVertexBufferView(UINT numBytes, UINT stride);

		/**@brief Creates a index buffer view and stores it.
		* 
		* @param[in] numBytes The number of bytes in the static buffer.
		* @param[in] format The number of bytes to get from one element to another in the static buffer.
		*/
		void CreateIndexBufferView(UINT numBytes, DXGI_FORMAT format);

		/**@brief Returns a constant reference to the vertex buffer view.
		*/
		const D3D12_VERTEX_BUFFER_VIEW& GetVertexBufferView();

		/**@brief Returns a constant reference to the vertex buffer view.
		*/
		const D3D12_INDEX_BUFFER_VIEW& GetIndexBufferView();

		/**@brief Frees the upload buffer memory.
		* 
		* Call when the command to copy data to the default buffer has been executed.
		*/
		void ReleaseUploader();

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> mStaticDefaultBuffer;
		Microsoft::WRL::ComPtr<ID3D12Resource> mStaticUploadBuffer;

		union
		{
			D3D12_VERTEX_BUFFER_VIEW mVertexBufferView{};
			D3D12_INDEX_BUFFER_VIEW mIndexBufferView;
		};
	};

	/** @class DynamicBuffer ""
	*	@brief This class stores data in a Direct3D 12 upload buffer.
	*/
	class DynamicBuffer
	{
	public:
		DynamicBuffer() = default;

		DynamicBuffer(const DynamicBuffer&) = delete;
		DynamicBuffer& operator=(const DynamicBuffer&) = delete;

		DynamicBuffer(DynamicBuffer&&) = default;

		/**@brief Unmaps the pointer to the dynamic buffer.
		*/
		~DynamicBuffer();

		/**@brief Returns the GPU virtual address of the first byte of the dynamic buffer.
		*/
		D3D12_GPU_VIRTUAL_ADDRESS GetGPUAddress() const;

		/**@brief Returns the stride of the dymanic buffer.
		*/
		const unsigned int& GetStride() const;

		/**@brief Returns the format of the dymanic buffer.
		*/
		const DXGI_FORMAT& GetFormat() const;

		/**@brief Creates and maps the dynamic buffer.
		* 
		* Call if you want to create a dynamic vertex buffer or dynamic constant buffer.
		* 
		* @param[in] device A Direct3D 12 device.
		* @param[in] numOfBytes The number of bytes you want to allocate for the dynamic buffer.
		* @param[in] stride The number of bytes to get from one element to another in the dynamic buffer.
		*/
		void CreateDynamicBuffer(const Microsoft::WRL::ComPtr<ID3D12Device>& device, UINT numOfBytes, UINT stride);

		/**@brief Creates and maps the dynamic buffer.
		* 
		* Call if you want to create a dynamic index buffer.
		* 
		* @param[in] device A Direct3D 12 device.
		* @param[in] numOfBytes The number of bytes you want to allocate for the dynamic buffer.
		* @param[in] format The number of bytes to get from one element to another in the dynamic buffer.
		*/
		void CreateDynamicBuffer(const Microsoft::WRL::ComPtr<ID3D12Device>& device, UINT numOfBytes, DXGI_FORMAT format);

		/**@brief Creates the constant buffer view and stores it in the specified descriptor heap.
		* 
		* @param[in] device A Direct3D 12 device.
		* @param[in] cbvHeap A descriptor heap for storing constant buffer descriptors.
		* @param[in] cbvSize The size of a depth stenicl descriptor.
		* @param[in] cbvHeapIndex The index of where to store the created descriptor in the descriptor heap.
		* @param[in] cBufferIndex The index of the constant data in the constant buffer you want to describe.
		*/
		void CreateConstantBufferView(const Microsoft::WRL::ComPtr<ID3D12Device>& device,
			const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& cbvHeap, UINT cbvSize, UINT cbvHeapIndex,
			UINT cBufferIndex);

		/**@brief Creates a vertex buffer view and stores it.
		* 
		* @param[in] numBytes The number of bytes in the dynamic buffer.
		*/
		void CreateVertexBufferView(UINT numBytes);

		/**@brief Creates a index buffer view and stores it.
		* 
		* @param[in] numBytes The number of bytes in the dynamic buffer.
		*/
		void CreateIndexBufferView(UINT numBytes);

		/**@brief Returns a constant reference to the vertex buffer view.
		*/
		const D3D12_VERTEX_BUFFER_VIEW& GetVertexBufferView();

		/**@brief Returns a constant reference to the vertex buffer view.
		*/
		const D3D12_INDEX_BUFFER_VIEW& GetIndexBufferView();

		/**@brief Copies data from the given data into the dynamic buffer.
		* Uses 0-indexing.
		* 
		* @param[in] data The data to copy in the dynamic buffer.
		* @param[in] numOfBytes The number of bytes to copy.
		*/
		void CopyData(UINT index, const void* data, UINT64 numOfBytes);

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> mDynamicBuffer;
		BYTE* mMappedData{ nullptr };

		union
		{
			UINT mStride;
			DXGI_FORMAT mFormat;
		};

		union
		{
			D3D12_VERTEX_BUFFER_VIEW mVertexBufferView{};
			D3D12_INDEX_BUFFER_VIEW mIndexBufferView;
		};
	};
}