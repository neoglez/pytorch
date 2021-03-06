#include <ATen/Context.h>
#include <ATen/StorageImpl.h>

namespace at {

StorageImpl::StorageImpl(
    at::ScalarType scalar_type,
    ptrdiff_t size,
    at::DataPtr data_ptr,
    at::Allocator* allocator,
    bool resizable)
    : scalar_type(scalar_type),
      data_ptr(std::move(data_ptr)),
      size(size),
      resizable(resizable),
      allocator(allocator),
      finalizer(nullptr) {}

StorageImpl::StorageImpl(
    at::ScalarType scalar_type,
    ptrdiff_t size,
    at::Allocator* allocator,
    bool resizable)
    : StorageImpl(
          scalar_type,
          size,
          allocator->allocate(at::elementSize(scalar_type) * size),
          allocator,
          resizable) {}

namespace detail {
Backend get_backend(StorageImpl* storage_impl) {
  if (storage_impl->data_ptr.device().is_cuda()) {
    return Backend::CUDA;
  }
  return Backend::CPU;
}
} // namespace detail
} // namespace at
